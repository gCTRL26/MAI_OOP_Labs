#pragma once

#include "NPCCreator.hpp"
#include <map>

class Factory {
  private:
    static std::map<std::string, std::unique_ptr<NPCCreator>> registry;
  public:
    static void RegisterType(const std::string& type, std::unique_ptr<NPCCreator> creator);
    static std::unique_ptr<NPC> CreateNPC(const std::string& type,
                                          const std::string& name,
                                          double x, double y);
    static std::unique_ptr<NPC> CreateNPCFromString(const std::string& data);
    static void Init();
};