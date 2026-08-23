#pragma once
#include "enemy.h"
#include "res_manager.h"
#include "rings/ring.h"

class Boss : public Enemy {
 public:
  Boss(CreatureStats const params, std::vector<Creature*>* const team,
       std::vector<Creature*>* const enemies, int* const maxenemies,
       ResourceManager* const Manager, CoreObserver* const observer,
       int const id);
  void SpecialAttack(Creature* const target);
  void Act(Creature* const target) override;
  void CheckHP() override;

 protected:
  int* MaxEnemies;
  bool SpecFlag = false;
  ResourceManager* Manager;
  std::vector<Creature*>* Enemies;
};