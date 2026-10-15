#pragma once
#include "enemy.h"
#include "res_manager.h"
#include "rings/ring.h"

class Boss : public Enemy {
 public:
  Boss(const CreatureStats params, std::vector<Creature*>* const team,
       std::vector<Creature*>* const enemies, int* const maxenemies,
       ResourceManager* const manager, CoreObserver* const observer,
       const int id);
  void SpecialAttack(Creature* const target);
  void Act(Creature* const target) override;
  void Checkhp() override;

 protected:
  int* max_enemies_;
  bool spec_preparing_ = false;
  ResourceManager* manager_;
  std::vector<Creature*>* enemies_;
};