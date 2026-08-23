#include "inventory.h"

Inventory::Inventory(Mage* const player, ResourceManager* const manager)
    : Player(player),
      Manager(manager),
      ChosenRing(nullptr),
      GetableRings(
          {"Blue Blood ring", "Heart ring", "Shiny ring", "Scaly ring"}) {}

void Inventory::Equipper(int const ringid, int const slot) {
  ChosenRing = &Player->Inventory.at(ringid);
  if (slot == Player->Arm.size()) {
    Player->Arm.push_back(*ChosenRing);
    ChosenRing->Stats.Equipped = true;
    ChosenRing->AddRingEffect(true);
  } else {
    Player->Arm[slot].Stats.Equipped = false;
    Player->Arm[slot].AddRingEffect(false);
    erase_if(Player->Arm, [](const Ring& r) { return !r.Stats.Equipped; });
    Player->Arm.push_back(*ChosenRing);
    ChosenRing->Stats.Equipped = true;
    ChosenRing->AddRingEffect(true);
  }
}

void Inventory::Unequipper(int const slot) {
  ChosenRing = &Player->Arm.at(slot);
  ChosenRing->Stats.Equipped = false;
  ChosenRing->AddRingEffect(true);
  erase_if(Player->Arm, [](const Ring& r) { return !r.Stats.Equipped; });
}

bool Inventory::AddRing(std::string const id) {
  if (!GetableRings.empty()) {
    std::string index = id;
    if (id == "") {
      index = GetableRings[rand() % GetableRings.size()];
    }
    Player->Inventory.push_back(Ring(Manager->GetRing(index), Player));
    return true;
  } else {
    return false;
  }
}