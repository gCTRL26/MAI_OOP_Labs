#include "dungeon.hpp"
#include "factory.hpp"
#include "visitor.hpp"
#include <iostream>

Dungeon::Dungeon() {
    Factory::Init();
    AddObserver(std::make_unique<FileObserver>());
    AddObserver(std::make_unique<ConsoleObserver>());
}

void Dungeon::AddNPC(std::unique_ptr<NPC> npc) {
    npcs.push_back(std::move(npc));
} 

void Dungeon::PrintNPCs() const {
    std::cout << "Total NPCs " << npcs.size() << "\n";
    for (size_t i = 0; i != npcs.size(); ++i) {
        const auto& npc = npcs[i];
        std::cout << i + 1 << ") " << npc->GetType() << " " << npc->GetName()
                  << " position - (" << npc->GetPos().first
                  << ", " << npc->GetPos().second << ")\n";
    }
}

void Dungeon::SaveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (size_t i = 0; i != npcs.size(); ++i) {
            const auto& npc = npcs[i];
            file << npc->GetType() << " " << npc->GetName()
                      << " " << npc->GetPos().first
                      << " " << npc->GetPos().second << "\n";
        }
        file.close();
        std::cout << "Saved " << npcs.size() << " NPCs to " << filename << std::endl;
    }
}

void Dungeon::LoadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        npcs.clear();
        std::string line;
        int loaded_count = 0;
        while (std::getline(file, line)) {
            auto npc = Factory::CreateNPCFromString(line);
            if (npc) {
                npcs.push_back(std::move(npc));
                ++loaded_count;
            }
        }
        file.close();
        std::cout << "Loaded " << loaded_count << " NPCs from " << filename << std::endl;
    }
}

void Dungeon::StartBattle(double range) {
    std::cout << "Battle starts now!\n";
    std::cout << "Total NPCs - " << npcs.size() << "\n";
    
    Visitor visitor(range);
    for (const auto& observer : observers) {
        visitor.AddObserver(observer.get());
    }
    visitor.Battle(npcs);
    std::cout << "Battle end. Remain " << npcs.size() << " NPCs" << std::endl;
}

void Dungeon::AddObserver(std::unique_ptr<Observer> observer) {
    observers.push_back(std::move(observer));
}