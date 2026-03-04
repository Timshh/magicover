#pragma once
#include "enemy.h"
#include "ring.h"

class Boss : public Enemy {
 public:
  Boss(Loader* loader = 0, int id = 0, std::vector<Creature*>* team = 0,
       int* maxEnemies = 0, std::vector<Creature*>* enemies = 0,
       int* maxStage = 0,
       int* currentStage = 0, int* coordX = 0, int* coordY = 0,
       int* normalAdd = 0,
       int* normalRand = 0, int* eliteAdd = 0, int* eliteRand = 0,
       std::vector<int>* getableRings = 0, std::vector<Ring>* inventory = 0,
       std::vector<std::vector<std::string>>* map = 0);
  int *MaxEnemies, *MaxStage, *CurrentStage, *CoordX, *CoordY,
      *NormalAdd, *NormalRand, *EliteAdd, *EliteRand;
  Loader *EnemyLoader;
  std::vector<Creature*> *Enemies;
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