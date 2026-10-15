#pragma once
#include <iostream>

#include "battle.h"
#include "core_observer.h"
#include "inventory.h"
#include "mage.h"
#include "map.h"
#include "res_manager.h"
#include "ring.h"
#include "room.h"
#include "ui_controller.h"

enum class GMStates { kBattle, kMap, kInventory, kRoom };

class Core {
 private:
  ResourceManager manager_;
  CoreObserver observer_;

 public:
  Core();

  std::vector<BattleActions> BattleGetActions();
  void BattleAct(const BattleActions action, const int choice1 = 0,
                 Creature* target = nullptr, const int choice2 = 0);
  void BattleFinish();
  void MapChooseRoom(const int way);

  void AddUI(UIController* const render);

  int RoomGetActions();
  void RoomAct(const int action);
  void RoomFinish();

  void RingEquip(const int ringid, const int slot);
  void RingUnequip(const int slot);

  void StartGame();
  int curr_stage;
  GMStates state;
  Battle gm_battle;
  Map gm_map;
  Inventory gm_inventory;
  Room gm_room;
  Mage player;

 private:
  bool is_fighting_boss_ = false;

  void ChangeStage();
};