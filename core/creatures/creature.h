#pragma once

#include <windows.h>

#include <cstdlib>
#include <iostream>
#include <vector>

#include "coreObserver.h"
#include "creature_stats.h"

class Creature {
 public:
  bool Alive = true;

  Creature(CreatureStats const params, std::vector<Creature*>* const team, CoreObserver* const observer, int const id);

  void virtual Act(Creature* const target);
  void virtual ReceiveDmg(float const damage, int const element,
                          float const status);
  void virtual CheckHP();
  CreatureStats Params;
  std::vector<Creature*>* Team;

 protected:
  int ID;
  CoreObserver* Observer;
};