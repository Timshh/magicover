#pragma once

#include "creature.h"

class Mage : public Creature {
 public:
  Mage(Stats params, std::vector<Creature*>* team);
  int IsBoss = 0;

  void SetColor(int color);
  void Attack(Creature* target);
  void Status();

  void virtual RecieveDmg(float damage, int element, float status) override;
  void virtual CheckHP() override;
  void virtual Act(Creature* target) override;

  std::string AtkText1, AtkText2, AtkText3, AtkText4, CalmText, HurtText,
      DamagedText, DeathText;
};