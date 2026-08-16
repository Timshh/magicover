#include "core.h"

Core::Core()
    : GMMap(),
      Manager("data/creatures.json", "data/rings.json"),
      Observer(),
      GMBattle(&Player, &Manager, &Observer),
      Player(Manager.GetCreature("Last Mage"), &GMBattle.Teammates, &Observer,
             -1),
      GMRoom(&Player, &GMInventory, &GMBattle),
      GMInventory(&Player, &Manager),
      CurrStage(0) {}

std::vector<BattleActions> Core::BattleGetActions() {
  return GMBattle.BattleGetActions();
}

void Core::BattleAct(BattleActions const action, int const choice1,
                     Creature* target, int const choice2) {
  GMBattle.BattleAct(action, choice1, target, choice2);
}

void Core::BattleFinish() {
  State = GMStates::Map;
  if (IsFightingBoss) {
    IsFightingBoss = false;
    ChangeStage();
  }
}

void Core::MapChooseRoom(int const way) {
  switch (GMMap.MapAct(way)) {
    case 0:
      State = GMStates::Inventory;
      break;
    case 1:
      IsFightingBoss = true;
      GMBattle.CreateBoss(CurrStage);
      State = GMStates::Battle;
      break;
    case 2:
      GMBattle.CreateEnemy();
      State = GMStates::Battle;
      break;
    case 3:
      GMBattle.CreateElite();
      State = GMStates::Battle;
      break;
    case 4:
      Player.Params.HP = Player.Params.HPMax;
      Player.Params.Mana = Player.Params.ManaMax;
      break;
    case 5:
      if (GMRoom.InitRoom(static_cast<RoomTypes>(
              rand() % static_cast<int>(RoomTypes::COUNT)))) {
        State = GMStates::Battle;
      }
      break;
  }
}

void Core::AddUI(UIController* const ui) { Observer.AddSubscriber(ui); }

int Core::RoomGetActions() { return GMRoom.RoomGetActions(); }

void Core::RoomAct(int const action) {
  if (GMRoom.RoomAct(action)) {
    State = GMStates::Battle;
  }
}

void Core::RoomFinish() { State = GMStates::Map; }

void Core::RingEquip(int const ringid, int const slot) {
  GMInventory.Equipper(ringid, slot);
}

void Core::RingUnequip(int const slot) { GMInventory.Unequipper(slot); }

void Core::StartGame() {
  Observer.CallAct(RenderActions::GameStart);
  GMBattle.CreateBoss(CurrStage);
  State = GMStates::Battle;
  IsFightingBoss = true;
}

void Core::ChangeStage() {
  Observer.CallAct(RenderActions::StageChange, -2, CurrStage);
  switch (CurrStage) {
    case 0:
      GMInventory.AddRing("Ring of memories");

      GMBattle.NormalEnemies = {"Hunter", "Warrior student", "Knight",
                                "Demon",  "Pseudo-Witch",    "Pseudo-Mage"};
      GMBattle.EliteEnemies = {"Archer", "Draconic hunter"};
      break;
    case 1:
      GMInventory.AddRing("Ring of arms");

      GMBattle.NormalEnemies = {"Demon", "Pseudo-Witch", "Pseudo-Mage",
                                "Automaton-Cleaner", "Automaton-Dog"};
      GMBattle.EliteEnemies = {"Automaton-Hunter", "Armored knight"};
      GMInventory.GetableRings.assign(
          {"Thorn ring", "Light ring", "Light ring", "Glass ring"});
      break;
    case 2:
      GMInventory.AddRing("Clockwork ring");

      GMBattle.NormalEnemies = {"Pseudo-Witch",      "Pseudo-Mage",
                                "Automaton-Cleaner", "Automaton-Dog",
                                "Witch candidate",   "Automaton-Dragon"};
      GMBattle.EliteEnemies = {"Slayer candidate", "Slayer"};
      GMInventory.GetableRings.assign({"Unstable ring", "Dice ring"});
      break;
    case 3:
      exit(0);
  }
  GMMap.CreateMap();
  CurrStage += 1;
}
