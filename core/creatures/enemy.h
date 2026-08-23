#pragma once

#include "creature.h"

class Enemy : public Creature {
 public:
  Enemy(CreatureStats params, std::vector<Creature*>* team,
        CoreObserver* const observer, int const id);

  void Attack(Creature* target);
  void Status();

  void ReceiveDmg(float damage, int element, float status) override;
  void CheckHP() override;
  void Act(Creature* target) override;
};