#pragma once

#include "NPC.hpp"
#include "observer.hpp"
#include <memory>
#include <vector>

class Dungeon {
  private:
    std::vector<std::unique_ptr<NPC>> npcs;
    std::vector<std::unique_ptr<Observer>> observers;
  public:
    Dungeon(); 
    void AddNPC(std::unique_ptr<NPC> npc);
    void PrintNPCs() const;
    void SaveToFile(const std::string& filename) const;
    void LoadFromFile(const std::string& filename);
    void StartBattle(double range);
    void AddObserver(std::unique_ptr<Observer> observer);
    ~Dungeon() = default;
};