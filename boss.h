#pragma once
#include "enemy.h"
#include "ring.h"
#include "res_manager.h"

class Boss : public Enemy {
 public:
  Boss(Stats params, std::vector<Creature*>* team, int* maxEnemies,
       std::vector<Creature*>* enemies, int* maxStage, int* currentStage,
       int* coordX, int* coordY, int* normalAdd, int* normalRand, int* eliteAdd,
       int* eliteRand, std::vector<int>* getableRings,
       std::vector<Ring>* inventory, std::vector<std::vector<std::string>>* map,
       ResourceManager* manager, Creature* player);
  int *MaxEnemies, *MaxStage, *CurrentStage, *CoordX, *CoordY,
      *NormalAdd, *NormalRand, *EliteAdd, *EliteRand;
  ResourceManager* EnemyManager;
  std::vector<Creature*>* Enemies;
  Creature* Player;
  std::vector<int> *GetableRings;
  std::vector<Ring> *Inventory;
  std::vector<std::vector<std::string>> *Map;
  int SpecAttackChance = 30;
  std::string Hint = "";
  bool SpecFlag = false;

  void SpecialAttack(Creature* target);
  void virtual Act(Creature* target) override;
  void virtual CheckHP() override;
};