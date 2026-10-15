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
  kStudents,
  kTrap,
  kAmbush,
  kRing,
  kDemon,
  kSkeleton,
  kEmpty,
  COUNT
};

class Room {
 public:
  Room(Mage* const player, Inventory* const inventory, Battle* const battle,
       CoreObserver* observer);

  int RoomGetActions();
  bool RoomAct(const int action);
  bool InitRoom(const RoomTypes type);

 private:
  Mage* player_;
  CoreObserver* observer_;

  RoomTypes room_type_;

  Inventory* gm_inventory_;
  Battle* gm_battle_;

  int actions_count_;
};