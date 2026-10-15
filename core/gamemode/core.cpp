#include "core.h"

Core::Core()
    : gm_map(),
      manager_("data/creatures.json", "data/rings.json"),
      observer_(),
      gm_battle(&player, &manager_, &observer_),
      player(manager_.GetCreature("Last Mage"), &gm_battle.teammates, &observer_,
             -1),
      gm_room(&player, &gm_inventory, &gm_battle, &observer_),
      gm_inventory(&player, &manager_),
      curr_stage(0) {}

std::vector<BattleActions> Core::BattleGetActions() {
  return gm_battle.BattleGetActions();
}

void Core::BattleAct(const BattleActions action, const int choice1,
                     Creature* target, const int choice2) {
  gm_battle.BattleAct(action, choice1, target, choice2);
}

void Core::BattleFinish() {
  state = GMStates::kMap;
  if (is_fighting_boss_) {
    is_fighting_boss_ = false;
    ChangeStage();
  }
}

void Core::MapChooseRoom(const int way) {
  switch (gm_map.MapAct(way)) {
    case 0:
      state = GMStates::kInventory;
      break;
    case 1:
      is_fighting_boss_ = true;
      gm_battle.CreateBoss(curr_stage);
      state = GMStates::kBattle;
      break;
    case 2:
      gm_battle.CreateEnemy();
      state = GMStates::kBattle;
      break;
    case 3:
      gm_battle.CreateElite();
      state = GMStates::kBattle;
      break;
    case 4:
      player.params.hp = player.params.hp_max;
      player.params.mana = player.params.mana_max;
      break;
    case 5:
      state = GMStates::kRoom;
      if (gm_room.InitRoom(static_cast<RoomTypes>(
              rand() % static_cast<int>(RoomTypes::COUNT)))) {
        state = GMStates::kBattle;
      }
      break;
  }
}

void Core::AddUI(UIController* const ui) { observer_.AddSubscriber(ui); }

int Core::RoomGetActions() { return gm_room.RoomGetActions(); }

void Core::RoomAct(int const action) {
  if (gm_room.RoomAct(action)) {
    state = GMStates::kBattle;
  }
}

void Core::RoomFinish() { state = GMStates::kMap; }

void Core::RingEquip(const int ringid, const int slot) {
  gm_inventory.Equipper(ringid, slot);
}

void Core::RingUnequip(const int slot) { gm_inventory.Unequipper(slot); }

void Core::StartGame() {
  observer_.CallAct(RenderActions::kGameStart);
  gm_battle.CreateBoss(curr_stage);
  state = GMStates::kBattle;
  is_fighting_boss_ = true;
}

void Core::ChangeStage() {
  observer_.CallAct(RenderActions::kStageChange, -2, curr_stage);
  switch (curr_stage) {
    case 0:
      gm_inventory.AddRing("Ring of memories");

      gm_battle.normal_enemies = {"Hunter", "Warrior student", "Knight",
                                "Demon",  "Pseudo-Witch",    "Pseudo-Mage"};
      gm_battle.elite_enemies = {"Archer", "Draconic hunter"};
      break;
    case 1:
      gm_inventory.AddRing("Ring of arms");

      gm_battle.normal_enemies = {"Demon", "Pseudo-Witch", "Pseudo-Mage",
                                "Automaton-Cleaner", "Automaton-Dog"};
      gm_battle.elite_enemies = {"Automaton-Hunter", "Armored knight"};
      gm_inventory.getable_rings.assign(
          {"Thorn ring", "Light ring", "Light ring", "Glass ring"});
      break;
    case 2:
      gm_inventory.AddRing("Clockwork ring");

      gm_battle.normal_enemies = {"Pseudo-Witch",      "Pseudo-Mage",
                                "Automaton-Cleaner", "Automaton-Dog",
                                "Witch candidate",   "Automaton-Dragon"};
      gm_battle.elite_enemies = {"Slayer candidate", "Slayer"};
      gm_inventory.getable_rings.assign({"Unstable ring", "Dice ring"});
      break;
    case 3:
      exit(0);
  }
  gm_map.CreateMap();
  curr_stage += 1;
}
