#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "ring.h"
#include "res_manager.h"
#include "enemy.h"
#include "consoleRenderer.h"
#include "boss.h"
#include "mage.h"
#include "map.h"
#include "renderer.h"

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

  ResourceManager ResManager = ResourceManager("data/creatures.json", "data/rings.json");
  ConsoleRenderer Render = ConsoleRenderer();
  Renderer GlobalRenderer = Renderer();
  
  std::vector<Creature*> Teammates, Enemies, StageBosses;
  Mage Player = Mage(ResManager.GetCreature("Last Mage"), &Teammates, &Render, &GlobalRenderer);
  Creature* Target = 0;
  Ring* ChosenRing;
  Ring* NewRing;
  Map GMMap = Map(&Render);

  void LocationAct(int roomType);

  void Gameloop();

  int TakeInt(int min, int max);

  // Battle
  void CreateBoss();
  void EnemyChooser();
  void ChangeStage();
  //Inventory
  bool NewRingChooser();
  void ShowRings();
  void InventoryChooser();
  void Equipper();
};