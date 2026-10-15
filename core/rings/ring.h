#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>
#include "creature.h"
#include "ring_stats.h"



class Ring {
 public:
  Ring(const RingStats stats, Creature* const owner);

  RingStats stats;

  float Clamp(const float num, const float min, const float max); 
  void RingAct();
  void AddRingEffect(const bool is_removing);

 private:
  std::string equipText_, unequipText_;
  Creature* owner_;
};