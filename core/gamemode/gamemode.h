#pragma once
#include <iostream>

#include "boss.h"
#include "consoleRenderer.h"
#include "enemy.h"
#include "mage.h"
#include "map.h"
#include "battle.h"
#include "inventory.h"
#include "renderer.h"
#include "res_manager.h"
#include "ring.h"

enum class GMStates { Battle, Map, Inventory };

class Gamemode {
 public:
  Gamemode();
  void Gameloop();

 private:
  int MaxStage = 0, CurrStage = 0, MaxEnemies, CoordX, CoordY;
  bool OSStudents = true, OSFreeRing = true, OSEmpty = true, ORDemon = true,
       ORDevil = true;
  GMStates State = GMStates::Battle;

  std::vector<std::string> GetableRings = {"Blue Blood ring", "Heart ring",
                                           "Shiny ring", "Scaly ring"},
                           NormalEnemies, EliteEnemies;

  ResourceManager Manager;
  ConsoleRenderer Render = ConsoleRenderer();
  Renderer GlobalRenderer = Renderer();

  std::vector<Creature*> Teammates, Enemies, StageBosses;
  Mage Player = Mage(Manager.GetCreature("Last Mage"), &Teammates, &Render,
                     &GlobalRenderer);
  
  Map GMMap;
  Battle GMBattle;
  Inventory GMInventory;

  int TakeInt(int min, int max);
  void LocationAct(int roomType);

  void ChangeStage();
};