#include "room.h"

Room::Room(Mage* const player, Inventory* const inventory, Battle* const battle)
    : Player(player), GMInventory(inventory), GMBattle(battle), ActionsCount(0) {}

int Room::RoomGetActions() { return ActionsCount; }

bool Room::RoomAct(int const action) {
  switch (RoomType) {
    case RoomTypes::Trap:
      switch (action) {
        case 0:
          GMInventory->AddRing();
          break;
        case 1:
          break;
      }
      break;
    case RoomTypes::Demon:
      switch (action) {
        case 0:
          Player->Params.HPMax -= 10;
          GMInventory->AddRing("Revengeance ring");
          break;
        case 1:
          break;
      }
      break;
    case RoomTypes::Skeleton:
      switch (action) {
        case 0:
          break;
        case 1:
          Player->Params.Mana = 0;
          Player->Params.ManaMax += 10;
          break;
      }
      break;
  }
  return false;
}

bool Room::InitRoom(RoomTypes const type) {
  RoomType = type;
  ActionsCount = 0;
  switch (RoomType) {
    case RoomTypes::Students:
      for (int i = 0; i < (rand() % 2 + 4); i++) {
        GMBattle->CreateEnemy("Warrior student");
      }
      return true;
    case RoomTypes::Trap:
      ActionsCount = 2;
      break;
    case RoomTypes::Ambush:
      GMBattle->CreateEnemy();
      GMBattle->CreateElite();
      return true;
    case RoomTypes::Demon:
      ActionsCount = 2;
      break;
    case RoomTypes::Ring:
      break;
    case RoomTypes::Skeleton:
      ActionsCount = 2;
      break;
    case RoomTypes::Empty:
      break;
  }
  return false;
}
