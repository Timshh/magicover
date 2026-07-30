#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>

#include "consoleRenderer.h"
#include "mage.h"
#include "res_manager.h"
#include "ring.h"

class Inventory {
 public:
  Inventory(ConsoleRenderer* const render, Mage* const player,
            std::vector<std::string>* const getableRings,
            ResourceManager* const manager);

  bool NewRingChooser();
  bool ShowRings();
  bool InventoryChooser();
  void Equipper();
  Ring* NewRing;

 private:
  
  Ring* ChosenRing;
  ConsoleRenderer* Render;
  Mage* Player;
  std::vector<std::string>* GetableRings;
  ResourceManager* Manager;
};