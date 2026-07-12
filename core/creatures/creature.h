#pragma once

#include <windows.h>

#include <cstdlib>
#include <iostream>
#include <vector>

#include "consoleRenderer.h"
#include "creatureObserver.h"
#include "creature_stats.h"

class Creature {
 public:
  bool Alive = true;

  Creature(CreatureStats params, std::vector<Creature*>* team,
           ConsoleRenderer* render, Renderer* renderer);

  void virtual Act(Creature* target);
  void virtual ReceiveDmg(float damage, int element, float status);
  void virtual CheckHP();
  CreatureStats Params;
  std::vector<Creature*>* Team;

 protected:
  ConsoleRenderer* Render;
  CreatureObserver PersonalObserver;
};