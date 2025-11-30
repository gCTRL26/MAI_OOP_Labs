#include "dungeon.hpp"
#include "factory.hpp"
#include <iostream>

int main() {
    Dungeon dungeon;
    
    dungeon.AddNPC(Factory::CreateNPC("Bear", "Baloo", 100, 200));
    dungeon.AddNPC(Factory::CreateNPC("Elf", "Legolas", 150, 180));
    dungeon.AddNPC(Factory::CreateNPC("Robber", "Robin", 120, 190));
    dungeon.AddNPC(Factory::CreateNPC("Robber", "John", 130, 200));
    dungeon.AddNPC(Factory::CreateNPC("Elf", "Arwen", 300, 400));
    dungeon.AddNPC(Factory::CreateNPC("Bear", "Winnie", 50, 50));
    
    std::cout << "=== Starter Pack NPCs ===" << std::endl;
    dungeon.PrintNPCs();
    
    dungeon.SaveToFile("dungeon.txt");
    
    std::cout << "\n=== Starting Battle ===" << std::endl;
    dungeon.StartBattle(100.0);
    
    std::cout << "\n=== After Battle ===" << std::endl;
    dungeon.PrintNPCs();
    
    std::cout << "\n=== Loading from File ===" << std::endl;
    dungeon.LoadFromFile("dungeon.txt");
    dungeon.PrintNPCs();
    
    return 0;
}