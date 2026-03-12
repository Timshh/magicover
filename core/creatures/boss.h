#pragma once
#include "enemy.h"
#include "rings/ring.h"
#include "res_manager.h"

class Boss : public Enemy {
 public:
  Boss(CreatureStats params, std::vector<Creature*>* team,
       std::vector<Creature*>* enemies, int* maxenemies,
       ResourceManager* resmanager, Renderer* render);
  std::vector<Creature*>* Enemies;
  int *MaxEnemies;
  ResourceManager *ResManager;
  int SpecAttackChance = 30;
  std::string Hint = "";
  bool SpecFlag = false;

  void SpecialAttack(Creature* target);
  void Act(Creature* target) override;
  void CheckHP() override;
};