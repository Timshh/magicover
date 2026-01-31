#pragma once
#include "enemy.h"
#include "ring.h"

class Boss : public Enemy {
 public:
  Boss(int ID);
  int SpecAttackChance = 30;
  std::string Hint = "";
  bool SpecFlag = false;
  float Clamp(float num, float min, float max);
  void SpecialAttack(float* Defence, int* NormalAdd, int* MainHP,
                     int* MaxEnemies, int* MaxStage, int* CurrentStage,
                     int* CoordX, int* NormalRand, int* EliteAdd,
                     int* EliteRand, int* CoordY,
                     std::vector<int>* GetableRings,
                     std::vector<Boss>* StageBosses,
                     std::vector<Enemy>* Enemies, 
                     std::vector<Ring>* Inventory,
                     std::vector<std::vector<std::string>>* Map);
  void virtual Act(float* Defence, int* NormalAdd, int* MainHP, int* MaxEnemies,
                   std::vector<Boss>* StageBosses, std::vector<Enemy>* Enemies,
                   int* MaxStage, int* CurrentStage, int* CoordX,
                   int* NormalRand, int* EliteAdd, int* EliteRand, int* CoordY,
                   std::vector<int>* GetableRings, 
                   std::vector<Ring>* Inventory,
                   std::vector<std::vector<std::string>>* Map);
  void virtual CheckHP(int* MaxStage, int* CurrentStage, int* CoordX,
                       int* NormalAdd, int* NormalRand, int* EliteAdd,
                       int* EliteRand, int* CoordY,
                       std::vector<int>* GetableRings,
                       std::vector<Boss>* StageBosses,
                       std::vector<Enemy>* Enemies, 
                       std::vector<Ring>* Inventory,
                       std::vector<std::vector<std::string>>* Map);
};