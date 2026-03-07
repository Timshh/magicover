#pragma once

#include "creature.h"

class Enemy : public Creature {
 public:
  Enemy(CreatureStats params, std::vector<Creature*>* team);

  void SetColor(int color);
  void Attack(Creature* target);
  void Status();

  void virtual RecieveDmg(float damage, int element, float status) override;
  void virtual CheckHP() override;
  void virtual Act(Creature* target) override;

  std::string AtkText1, AtkText2, AtkText3, AtkText4, CalmText, HurtText,
      DamagedText, DeathText;
};