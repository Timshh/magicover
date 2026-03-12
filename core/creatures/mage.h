#pragma once

#include "creature.h"
#include "ring.h"

class Mage : public Creature {
 public:
  Mage(CreatureStats params, std::vector<Creature*>* team, Renderer* render);
  std::vector<Ring> Inventory;
  std::vector<Ring> Arm;

  void ReceiveDmg(float damage, int element, float status) override;
  void CheckHP() override;
  void Act(Creature* target) override;


  void Status();
  void Magic(Creature* target);
  void Offence();
};