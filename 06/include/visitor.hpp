#pragma once

#include "NPC.hpp"
#include <memory>
#include "observer.hpp"
#include <vector>

class Visitor {
  private:
    double range;
    std::vector<Observer*> observers;
  public:
    Visitor(double range);
    void AddObserver(Observer* observer);
    void RemoveObserver(Observer* observer);
    void NotifyObserver(const std::string& mes) const;
    bool Visit(NPC* attacker, NPC* terpila);
    void Battle(std::vector<std::unique_ptr<NPC>>& npcs);
};