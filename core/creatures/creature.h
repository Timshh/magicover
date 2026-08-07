#pragma once

#include <windows.h>

#include <cstdlib>
#include <iostream>
#include <vector>

#include "creatureObserver.h"
#include "creature_stats.h"

class Creature {
 public:
  bool Alive = true;

  Creature(CreatureStats const params, std::vector<Creature*>* const team);

  void virtual Act(Creature* const target);
  void virtual ReceiveDmg(float const damage, int const element,
                          float const status);
  void virtual CheckHP();
  CreatureStats Params;
  std::vector<Creature*>* Team;

 protected:
  CreatureObserver PersonalObserver;
};