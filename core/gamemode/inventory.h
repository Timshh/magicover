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

  std::vector<std::string> GetableRings;
  void Equipper(int const ringid, int const slot);
  void Unequipper(int const slot);
  void AddRing(std::string const id = "");

 private:
  Ring* ChosenRing;
  Mage* Player;
  ResourceManager* Manager;
};