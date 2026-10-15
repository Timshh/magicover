#pragma once

#include "creature.h"

class Enemy : public Creature {
 public:
  Enemy(const CreatureStats params, std::vector<Creature*>* team,
        CoreObserver* const observer, const int id);

  void Attack(Creature* target);
  void Status();

  void Receivedamage(const float damage, const int element,
                     const float status) override;
  void Checkhp() override;
  void Act(Creature* target) override;
};