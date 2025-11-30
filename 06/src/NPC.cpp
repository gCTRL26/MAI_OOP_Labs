#include "NPC.hpp"
#include "visitor.hpp"
#include <cmath>
#include <utility>

bool NPC::CanAttack(NPC* terpila) const {
    if (!terpila) {
        return false;
    }

    std::string atk_type = this->GetType();
    std::string def_type = terpila->GetType();

    if (atk_type == "Bear" && def_type == "Elf") {
        return true;
    }

    if (atk_type == "Elf" && def_type == "Robber") {
        return true;
    }

    if (atk_type == "Robber" && def_type == "Robber") {
        return true;
    }

    return false;
}

std::string NPC::GetMessage(NPC* terpila) const {
    if (!terpila) {
        return "";
    }

    return this->GetType() + " " + this->GetName() + " kills " + terpila->GetType() + " " + terpila->GetName();
}

NPC::NPC(const std::string& name, double x, double y) : name(name), x(x), y(y) {}

bool NPC::Accept(Visitor& visitor, NPC* other) {
    return visitor.Visit(this, other);
}

std::string NPC::GetName() const {
    return name;
}

std::pair<double, double> NPC::GetPos() const {
    return std::make_pair(x, y);
}

void NPC::SetPos(int newx, int newy) {
    x = newx;
    y = newy;
}

double NPC::Distance(const NPC* other) const {
    if (!other) {
        return 0;
    }

    return std::sqrt(pow(x - other->x, 2) + pow(y - other->y, 2));
}

Bear::Bear(const std::string& name, double x, double y) : NPC(name, x, y) {}
std::string Bear::GetType() const { 
    return "Bear"; 
}

Elf::Elf(const std::string& name, double x, double y) : NPC(name, x, y) {}
std::string Elf::GetType() const { 
    return "Elf"; 
}

Robber::Robber(const std::string& name, double x, double y) : NPC(name, x, y) {}
std::string Robber::GetType() const { 
    return "Robber"; 
}