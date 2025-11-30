#include "factory.hpp"
#include <sstream>
#include <utility>

std::map<std::string, std::unique_ptr<NPCCreator>> Factory::registry;

void Factory::RegisterType(const std::string& type, std::unique_ptr<NPCCreator> creator) {
    registry[type] = std::move(creator);
}

std::unique_ptr<NPC> Factory::CreateNPC(const std::string& type, const std::string& name, double x, double y) {
    auto it = registry.find(type);
    if (it != registry.end() && it->second) {
        return it->second->Create(name, x, y);
    }
    return nullptr;
}

std::unique_ptr<NPC> Factory::CreateNPCFromString(const std::string& data) {
    std::istringstream iss(data);
    std::string type;
    std::string name;
    double x;
    double y;
    if (iss >> type >> name >> x >> y) {
        return CreateNPC(type, name, x, y);
    }
    return nullptr;
}

void Factory::Init() {
    RegisterType("Bear", std::make_unique<BearCreator>());
    RegisterType("Elf", std::make_unique<ElfCreator>());
    RegisterType("Robber", std::make_unique<RobberCreator>());
}