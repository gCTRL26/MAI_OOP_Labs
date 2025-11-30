#pragma once

#include <string>
#include <utility>

class Visitor;

class NPC {
  protected:
    double x;
    double y;
    std::string name;
  public:
    NPC(const std::string& name, double x, double y);
    virtual ~NPC() = default;
    virtual std::string GetType() const = 0;
    virtual bool Accept(Visitor& visitor, NPC* other);
    std::string GetName() const;
    std::pair<double, double> GetPos() const;
    void SetPos(int x, int y);
    double Distance(const NPC* other) const;
    bool CanAttack(NPC* terpila) const;
    std::string GetMessage(NPC* terpila) const;
};

class Bear : public NPC {
  public:
    Bear(const std::string& name,  double x, double y);
    std::string GetType() const override;
};

class Elf : public NPC {
  public:
    Elf(const std::string& name, double x, double y);
    std::string GetType() const override;
};

class Robber : public NPC {
  public:
    Robber(const std::string& name, double x, double y);
    std::string GetType() const override;
};