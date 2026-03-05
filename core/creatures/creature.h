#pragma once

#include <cstdlib>
#include <iostream>
#include <vector>
#include <windows.h>
#include "stats.h"

class Creature {
 public:
  bool Alive = true;
  Stats Params;
  std::vector<Creature*>* Team;

  Creature(Stats params, std::vector<Creature*>* team);
  
  void virtual Act(Creature* target);
  void virtual RecieveDmg(float damage, int element, float status);
  void virtual CheckHP();
};