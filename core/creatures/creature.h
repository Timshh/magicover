#pragma once

#include <cstdlib>
#include <iostream>
#include <vector>
#include <windows.h>
#include "creature_stats.h"
#include "renderer.h"

class Creature {
 public:
  bool Alive = true;
  CreatureStats Params;
  std::vector<Creature*>* Team;
  Renderer* Render;

  Creature(CreatureStats params, std::vector<Creature*>* team, Renderer* render);
  
  void virtual Act(Creature* target);
  void virtual ReceiveDmg(float damage, int element, float status);
  void virtual CheckHP();
};