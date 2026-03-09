#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>
#include "creature.h"
#include "ring_stats.h"



class Ring {
 public:
  Ring(RingStats stats, Creature* owner);
  RingStats Stats;
  std::string EquipText, UnequipText;
  Creature* Owner;

  float Clamp(float num, float min, float max); 
  void RingAct();
  void AddRingEffect(bool isRemoving);
};