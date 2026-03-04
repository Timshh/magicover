#pragma once

#include <cstdlib>
#include <iostream>
#include <vector>
#include <windows.h>
#include "loader.h"

class Creature {
 public:
  int ID;
  bool Alive = true;
  Stats Params;
  std::vector<Creature*>* Team;

  Creature(Loader* loader = 0, int id = 0, std::vector<Creature*>* team = 0);
  
  void virtual Act(Creature* target);
  void virtual RecieveDmg(float damage, int element, float status);
  void virtual CheckHP();
};