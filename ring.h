#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>
#include "creature.h"



class Ring {
 public:
  Ring(int id, Creature* owner);
  int ID;
  bool Uneqippable = true, Equipped = false;
  std::string Name, Description, EquipText, UnequipText;
  std::vector<int> PEffects;
  std::vector<float> PStats;
  std::vector<int> AEffects;
  std::vector<float> AStats;
  Creature* Owner;

  float Clamp(float num, float min, float max); 
  void RingAct();
  void AddRingEffect(bool isRemoving);
};