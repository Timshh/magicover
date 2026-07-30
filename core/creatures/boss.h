#pragma once
#include "enemy.h"
#include "rings/ring.h"
#include "res_manager.h"

class Boss : public Enemy {
 public:
  Boss(CreatureStats params, std::vector<Creature*>* team,
       std::vector<Creature*>* enemies, int* maxenemies,
       ResourceManager* Manager, ConsoleRenderer* render,
       Renderer* renderer);
  void SpecialAttack(Creature* target);
  void Act(Creature* target) override;
  void CheckHP() override;

 protected:
  int* MaxEnemies;
  bool SpecFlag = false;
  Renderer* GlobalRenderer;
  ResourceManager* Manager;
  std::vector<Creature*>* Enemies;
};