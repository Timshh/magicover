#pragma once

#include "creature.h"
#include "ring.h"

class Mage : public Creature {
 public:
  Mage(const CreatureStats params, std::vector<Creature*>* const team,
       CoreObserver* const observer, const int id);
  std::vector<Ring> inventory;
  std::vector<Ring> arm;

  void Receivedamage(const float damage, const int element,
                     const float status) override;
  void Checkhp() override;
  void Act(Creature* const target) override;


  void Status();
  void Magic(Creature* const target);
  void Offence(const int choice);
};