#pragma once
#include <iostream>

#include "battle.h"
#include "boss.h"
#include "enemy.h"
#include "inventory.h"
#include "mage.h"
#include "map.h"
#include "res_manager.h"
#include "ring.h"

enum class RoomTypes {
  Students,
  Trap,
  Ambush,
  Ring,
  Demon,
  Skeleton,
  Empty,
  COUNT
};

class Room {
 public:
  Room(Mage* const player, Inventory* const inventory, Battle* const battle);

  int RoomGetActions();
  bool RoomAct(int const action);
  bool InitRoom(RoomTypes const type);

 private:
  Mage* Player;

  RoomTypes RoomType;

  Inventory* GMInventory;
  Battle* GMBattle;

  int ActionsCount;
};