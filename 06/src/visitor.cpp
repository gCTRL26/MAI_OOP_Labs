#include "visitor.hpp"
#include <set>

Visitor::Visitor(double range) : range(range) {}

void Visitor::AddObserver(Observer* observer) {
    if (observer) {
        observers.push_back(observer);
    }
}

void Visitor::RemoveObserver(Observer* observer) {
    for (auto it = observers.begin(); it != observers.end(); ) {
        if (*it == observer) {
            it = observers.erase(it);
        } else {
            ++it;
        }
    }
}

void Visitor::NotifyObserver(const std::string& mes) const {
    for (Observer* observer : observers) {
        observer->Update(mes);
    }
}

bool Visitor::Visit(NPC* attacker, NPC* terpila) {
    if (!attacker || !terpila) {
        return false;
    }

    if (attacker->CanAttack(terpila)) {
        NotifyObserver(attacker->GetMessage(terpila));
        return true;
    }
    return false;
}

void Visitor::Battle(std::vector<std::unique_ptr<NPC>>& npcs) {
    if (npcs.size() < 2) {
        return;
    }   
    std::set<size_t> killed;
    for (size_t i = 0; i != npcs.size(); ++i) {
        if (killed.count(i)) {
            continue;
        }
        for (size_t j = i + 1; j != npcs.size(); ++j) {
            if (killed.count(j)) {
                continue;
            }
            if (npcs[i]->Distance(npcs[j].get()) <= range) {
                bool killed1 = npcs[i]->Accept(*this, npcs[j].get());
                bool killed2 = npcs[j]->Accept(*this, npcs[i].get());
                if (killed1) {
                    killed.insert(j);
                }
                if (killed2) {
                    killed.insert(i);
                    break;
                }
            }
        }   
    }

    for (auto it = killed.rbegin(); it != killed.rend(); ++it) {
        npcs.erase(npcs.begin() + *it);
    }
}