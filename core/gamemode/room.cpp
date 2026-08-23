#include "room.h"

Room::Room(Mage* const player, Inventory* const inventory, Battle* const battle,
           CoreObserver* observer)
    : Player(player), GMInventory(inventory), GMBattle(battle), ActionsCount(0), Observer(observer) {}

int Room::RoomGetActions() { return ActionsCount; }

bool Room::RoomAct(int const action) {
  switch (RoomType) {
    case RoomTypes::Trap:
      switch (action) {
        case 1:
          Observer->CallAct(RenderActions::RoomAct, -1, 2, 1);
          ActionsCount = 0;
          break;
        case 2:
          if (GMInventory->AddRing()) {
            Observer->CallAct(RenderActions::RoomAct, -1, 2, 2);
            Observer->CallAct(RenderActions::NewRing);
          } else {
            Observer->CallAct(RenderActions::RoomAct, -1, 2, 3);
          }
          ActionsCount = 0;
          break;
      }
      break;
    case RoomTypes::Demon:
      switch (action) {
        case 1:
          Player->Params.HPMax -= 10;
          Observer->CallAct(RenderActions::RoomAct, -1, 4, 1);
          GMInventory->AddRing("Revengeance ring");
          ActionsCount = 0;
          break;
        case 2:
          Observer->CallAct(RenderActions::RoomAct, -1, 4, 2);
          break;
      }
      break;
    case RoomTypes::Skeleton:
      switch (action) {
        case 1:
          Observer->CallAct(RenderActions::RoomAct, -1, 6, 1);
          ActionsCount = 0;
          break;
        case 2:
          Observer->CallAct(RenderActions::RoomAct, -1, 6, 2);
          Player->Params.Mana = 0;
          Player->Params.ManaMax += 10;
          ActionsCount = 0;
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
      Observer->CallAct(RenderActions::RoomAct, -1, 1);
      for (int i = 0; i < (rand() % 2 + 4); i++) {
        GMBattle->CreateEnemy("Warrior student");
      }
      return true;
    case RoomTypes::Trap:
      Observer->CallAct(RenderActions::RoomAct, -1, 2);
      ActionsCount = 2;
      break;
    case RoomTypes::Ambush:
      Observer->CallAct(RenderActions::RoomAct, -1, 3);
      GMBattle->CreateEnemy();
      GMBattle->CreateElite();
      return true;
    case RoomTypes::Demon:
      Observer->CallAct(RenderActions::RoomAct, -1, 4);
      ActionsCount = 2;
      break;
    case RoomTypes::Ring:
      if (GMInventory->AddRing()) {
        Observer->CallAct(RenderActions::RoomAct, -1, 5, 1);
        Observer->CallAct(RenderActions::NewRing);
      } else {
        Observer->CallAct(RenderActions::RoomAct, -1, 5, 2);
      }
      break;
    case RoomTypes::Skeleton:
      Observer->CallAct(RenderActions::RoomAct, -1, 6);
      ActionsCount = 2;
      break;
    case RoomTypes::Empty:
      Observer->CallAct(RenderActions::RoomAct, -1, 7);
      break;
  }
  return false;
}
