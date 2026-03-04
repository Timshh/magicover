#pragma once

#include "creature.h"

class Enemy : public Creature {
 public:
  Enemy(Loader* loader = 0, int id = 0, std::vector<Creature*>* team = 0);
  int IsBoss = 0;

  void SetColor(int color);
  void Attack(Creature* target);
  void Stats();

  void virtual RecieveDmg(float damage, int element, float status) override;
  void virtual CheckHP() override;
  void virtual Act(Creature* target) override;

  std::string AtkText1, AtkText2, AtkText3, AtkText4, CalmText, HurtText,
      DamagedText, DeathText;
};