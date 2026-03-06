#pragma once

#include "creature.h"
#include "ring.h"

class Mage : public Creature {
 public:
  Mage(Stats params, std::vector<Creature*>* team);
  std::vector<Ring> Inventory;
  std::vector<Ring> Arm;

  void virtual RecieveDmg(float damage, int element, float status) override;
  void virtual CheckHP() override;
  void virtual Act(Creature* target) override;


  void SetColor(int color);
  void Status();
  void Magic(Creature* target);
  void Offence();
};