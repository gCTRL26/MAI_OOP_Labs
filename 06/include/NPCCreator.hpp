#pragma once

#include "NPC.hpp"
#include <memory>

class NPCCreator {
  public:
    virtual ~NPCCreator() = default;
    virtual std::unique_ptr<NPC> Create(const std::string& name, double x, double y) = 0;
};

class BearCreator : public NPCCreator {
  public:
    std::unique_ptr<NPC> Create(const std::string& name, double x, double y) override;
};

class ElfCreator : public NPCCreator {
  public:
    std::unique_ptr<NPC> Create(const std::string& name, double x, double y) override;
};

class RobberCreator : public NPCCreator {
  public:
    std::unique_ptr<NPC> Create(const std::string& name, double x, double y) override;
};