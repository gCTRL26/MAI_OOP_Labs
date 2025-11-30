#include "NPCCreator.hpp"

std::unique_ptr<NPC> BearCreator::Create(const std::string& name, double x, double y) {
    return std::make_unique<Bear>(name, x, y);
}

std::unique_ptr<NPC> ElfCreator::Create(const std::string& name, double x, double y) {
    return std::make_unique<Elf>(name, x, y);
}

std::unique_ptr<NPC> RobberCreator::Create(const std::string& name, double x, double y) {
    return std::make_unique<Robber>(name, x, y);
}