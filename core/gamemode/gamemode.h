#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "ring.h"
#include "res_manager.h"
#include "enemy.h"
#include "boss.h"
#include "mage.h"



class Gamemode {
 public:
  Gamemode();
  int MaxStage, CurrStage, MaxEnemies = 2, CoordX = 0, CoordY = 3, NormalRand,
                           NormalAdd, EliteRand, EliteAdd, State;
  bool OSStudents = true, OSFreeRing = true, OSEmpty = true, ORDemon = true,
       ORDevil = true;
  std::vector<int> GetableRings = {1, 2, 3, 4};
  std::vector<std::vector<std::string>> Map;

  ResourceManager ResManager = ResourceManager("data/creatures.json");
  std::vector<Creature*> Teammates;
  std::vector<Creature*> Enemies;
  std::vector<Creature*> StageBosses;
  Mage Player = Mage(ResManager.GetCreature(2000), &Teammates);
  Creature* Target = 0;
  Ring* ChosenRing;
  Ring NewRing = Ring(1, &Player);

  void Gameloop();

  void SetColor(int color);
  float Clamp(float num, float min, float max);
  int TakeInt(int min, int max);

  void Create_enemies();
  void EnemyChooser();
  
  void LocationAct();
  void DrawMap();

  bool NewRingChooser();
  void ShowRings();
  void InventoryChooser();
  void Equipper();
};