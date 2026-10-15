#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>

#include "mage.h"
#include "res_manager.h"
#include "ring.h"

class Inventory {
 public:
  Inventory(Mage* const player, ResourceManager* const manager);

  std::vector<std::string> getable_rings;
  void Equipper(const int ringid, const int slot);
  void Unequipper(const int slot);
  bool AddRing(const std::string id = "");

 private:
  Ring* chosen_ring_;
  Mage* player_;
  ResourceManager* manager_;
};