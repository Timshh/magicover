#include "room.h"

Room::Room(Mage* const player, Inventory* const inventory, Battle* const battle,
           CoreObserver* observer)
    : player_(player), gm_inventory_(inventory), gm_battle_(battle), actions_count_(0), observer_(observer) {}

int Room::RoomGetActions() { return actions_count_; }

bool Room::RoomAct(const int action) {
  switch (room_type_) {
    case RoomTypes::kTrap:
      switch (action) {
        case 1:
          observer_->CallAct(RenderActions::kRoomAct, -1, 2, 1);
          actions_count_ = 0;
          break;
        case 2:
          if (gm_inventory_->AddRing()) {
            observer_->CallAct(RenderActions::kRoomAct, -1, 2, 2);
            observer_->CallAct(RenderActions::kNewRing);
          } else {
            observer_->CallAct(RenderActions::kRoomAct, -1, 2, 3);
          }
          actions_count_ = 0;
          break;
      }
      break;
    case RoomTypes::kDemon:
      switch (action) {
        case 1:
          player_->params.hp_max -= 10;
          observer_->CallAct(RenderActions::kRoomAct, -1, 4, 1);
          gm_inventory_->AddRing("Revengeance ring");
          actions_count_ = 0;
          break;
        case 2:
          observer_->CallAct(RenderActions::kRoomAct, -1, 4, 2);
          break;
      }
      break;
    case RoomTypes::kSkeleton:
      switch (action) {
        case 1:
          observer_->CallAct(RenderActions::kRoomAct, -1, 6, 1);
          actions_count_ = 0;
          break;
        case 2:
          observer_->CallAct(RenderActions::kRoomAct, -1, 6, 2);
          player_->params.mana = 0;
          player_->params.mana_max += 10;
          actions_count_ = 0;
          break;
      }
      break;
  }
  return false;
}

bool Room::InitRoom(const RoomTypes type) {
  room_type_ = type;
  actions_count_ = 0;
  switch (room_type_) {
    case RoomTypes::kStudents:
      observer_->CallAct(RenderActions::kRoomAct, -1, 1);
      for (int i = 0; i < (rand() % 2 + 4); i++) {
        gm_battle_->CreateEnemy("Warrior student");
      }
      return true;
    case RoomTypes::kTrap:
      observer_->CallAct(RenderActions::kRoomAct, -1, 2);
      actions_count_ = 2;
      break;
    case RoomTypes::kAmbush:
      observer_->CallAct(RenderActions::kRoomAct, -1, 3);
      gm_battle_->CreateEnemy();
      gm_battle_->CreateElite();
      return true;
    case RoomTypes::kDemon:
      observer_->CallAct(RenderActions::kRoomAct, -1, 4);
      actions_count_ = 2;
      break;
    case RoomTypes::kRing:
      if (gm_inventory_->AddRing()) {
        observer_->CallAct(RenderActions::kRoomAct, -1, 5, 1);
        observer_->CallAct(RenderActions::kNewRing);
      } else {
        observer_->CallAct(RenderActions::kRoomAct, -1, 5, 2);
      }
      break;
    case RoomTypes::kSkeleton:
      observer_->CallAct(RenderActions::kRoomAct, -1, 6);
      actions_count_ = 2;
      break;
    case RoomTypes::kEmpty:
      observer_->CallAct(RenderActions::kRoomAct, -1, 7);
      break;
  }
  return false;
}
