#pragma once

#include <windows.h>


#include <vector>

#include "core_observer.h"
#include "creature_stats.h"

class Creature {
 public:
  bool alive = true;

  Creature(const CreatureStats params, std::vector<Creature*>* const team,
           CoreObserver* const observer, const int id);

  virtual void Act(Creature* const target);
  virtual void Receivedamage(const float damage, const int element,
                             const float status);
  virtual void Checkhp();
  CreatureStats params;
  std::vector<Creature*>* team;

 protected:
  int id_;
  CoreObserver* observer_;
};