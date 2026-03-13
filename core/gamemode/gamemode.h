#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "ring.h"
#include "res_manager.h"
#include "enemy.h"
#include "renderer.h"
#include "boss.h"
#include "mage.h"

enum class GMStates { 
    Battle,
    Map,
    Inventory
};

class Gamemode {
 public:
  Gamemode();
  int MaxStage, CurrStage, MaxEnemies, CoordX, CoordY;
  bool OSStudents = true, OSFreeRing = true, OSEmpty = true, ORDemon = true,
       ORDevil = true;
  GMStates State;

  std::vector<std::string> GetableRings = {"Blue Blood ring", "Heart ring", "Shiny ring", "Scaly ring"}, NormalEnemies, EliteEnemies;
  std::vector<std::vector<std::string>> Map;

  ResourceManager ResManager = ResourceManager("data/creatures.json", "data/rings.json");
  Renderer Render = Renderer();
  
  std::vector<Creature*> Teammates, Enemies, StageBosses;
  Mage Player = Mage(ResManager.GetCreature("Last Mage"), &Teammates, &Render);
  Creature* Target = 0;
  Ring* ChosenRing;
  Ring* NewRing;

  void Gameloop();

  int TakeInt(int min, int max);
  // Battle
  void CreateBoss();
  void EnemyChooser();
  void ChangeStage();
  //Map
  void LocationAct();
  void DrawMap();
  //Inventory
  bool NewRingChooser();
  void ShowRings();
  void InventoryChooser();
  void Equipper();
};