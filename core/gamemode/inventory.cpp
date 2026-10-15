#include "inventory.h"

Inventory::Inventory(Mage* const player, ResourceManager* const manager)
    : player_(player),
      manager_(manager),
      chosen_ring_(nullptr),
      getable_rings(
          {"Blue Blood ring", "Heart ring", "Shiny ring", "Scaly ring"}) {}

void Inventory::Equipper(const int ringid, const int slot) {
  chosen_ring_ = &player_->inventory.at(ringid);
  if (slot == player_->arm.size()) {
    player_->arm.push_back(*chosen_ring_);
    chosen_ring_->stats.equipped = true;
    chosen_ring_->AddRingEffect(true);
  } else {
    player_->arm[slot].stats.equipped = false;
    player_->arm[slot].AddRingEffect(false);
    erase_if(player_->arm, [](const Ring& r) { return !r.stats.equipped; });
    player_->arm.push_back(*chosen_ring_);
    chosen_ring_->stats.equipped = true;
    chosen_ring_->AddRingEffect(true);
  }
}

void Inventory::Unequipper(const int slot) {
  chosen_ring_ = &player_->arm.at(slot);
  chosen_ring_->stats.equipped = false;
  chosen_ring_->AddRingEffect(true);
  erase_if(player_->arm, [](const Ring& r) { return !r.stats.equipped; });
}

bool Inventory::AddRing(const std::string id) {
  if (!getable_rings.empty()) {
    std::string index = id;
    if (id == "") {
      index = getable_rings[rand() % getable_rings.size()];
    }
    player_->inventory.push_back(Ring(manager_->GetRing(index), player_));
    return true;
  } else {
    return false;
  }
}