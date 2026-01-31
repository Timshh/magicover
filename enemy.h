#pragma once

#include <cstdlib>
#include <iostream>
#include <vector>
#include <windows.h>

class Enemy {
 public:
  Enemy(int ID = 0);
  bool Alive = true;
  int Type, IsBoss = 0, DamageRand = 0;
  void SetColor(int color);
  void Attack(int* MainHP, float* Defence);
  void Stats(std::vector<Enemy>* Enemies);
  void RecieveDmg(float* Dmg, float* DamageMult, int* Element, float* Status,
                  float* StatusMult, std::vector<Enemy>* Enemies);
  void virtual CheckHP(std::vector<Enemy>* Enemies);
  void virtual Act(int* MainHP, float* Defence, std::vector<Enemy>* Enemies);
  float HP = 0, HPMax = 0, Damage = 0, Resist = 1, FlameResist = 1,
        FrostResist = 1, DarkResist = 1, PsychoResist = 1, Flame = 0, Frost = 0,
        Dark = 0, Psycho = 0;
  std::string Name, AtkText1, AtkText2, AtkText3, AtkText4, CalmText, HurtText,
      DamagedText, DeathText;
};