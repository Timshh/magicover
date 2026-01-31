#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>



class Ring {
 public:
  Ring(int ID = 0);
  int Type;
  bool Uneqippable = true, Equipped = false;
  std::string Name, Description, EquipText, UnequipText;
  std::vector<int> PEffects;
  std::vector<float> PStats;
  std::vector<int> AEffects;
  std::vector<float> AStats;
  float Clamp(float num, float min, float max); 
  void RingAct(int* MainHP, int* MainHPMax, int* Mana, int* ManaMax);
  void AddRingEffect(int Mult, int* MainHP, int* MainHPMax, int* Mana,
                     int* ManaMax, int* SecondAtkChance, float* DefaultDefence,
                     float* DefaultStatusMult, int* SecondChance,
                     float* DefaultDamageMult);
};