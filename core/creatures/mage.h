#pragma once

#include "creature.h"
#include "ring.h"

class Mage : public Creature {
 public:
  Mage(CreatureStats const params, std::vector<Creature*>* const team);
  std::vector<Ring> Inventory;
  std::vector<Ring> Arm;

  void ReceiveDmg(float const damage, int const element,
                  float const status) override;
  void CheckHP() override;
  void Act(Creature* const target) override;


  void Status();
  void Magic(Creature* const target);
  void Offence(int const choice);
};