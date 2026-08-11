#pragma once
#include <iostream>

#include "battle.h"
#include "boss.h"
#include "coreObserver.h"
#include "enemy.h"
#include "inventory.h"
#include "mage.h"
#include "map.h"
#include "res_manager.h"
#include "ring.h"
#include "room.h"
#include "uiController.h"

enum class GMStates { Battle, Map, Inventory };

class Core {
 private:
  ResourceManager Manager;
  CoreObserver Observer;

 public:
  Core();

  std::vector<BattleActions> BattleGetActions();
  void BattleAct(BattleActions const action, int const choice1 = 0,
                 Creature* target = nullptr, int const choice2 = 0);
  void BattleFinish();
  void MapChooseRoom(int const way);

  void AddUI(UIController* const render);

  int RoomGetActions();
  void RoomAct(int const action);
  void RoomFinish();

  void RingEquip(int const ringid, int const slot);
  void RingUnequip(int const slot);

  void StartGame();
  int CurrStage;
  GMStates State;
  Battle GMBattle;
  Mage Player;

 private:
  

  Map GMMap;

  Inventory GMInventory;
  Room GMRoom;

  void ChangeStage();
};