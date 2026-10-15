#include "mage.h"

Mage::Mage(const CreatureStats params, std::vector<Creature*>* const team,
           CoreObserver* const observer, const int id)
    : Creature(params, team, observer, id) {}

void Mage::Act(Creature* const target) { Creature::Act(target); }

void Mage::Status() {
  params.mana = min(params.mana + 15, params.mana_max);
  for (Ring& currRing : arm) {
    currRing.RingAct();
  }
  params.defence = params.default_defence;
  params.damage_mult = params.default_damage_mult;
  params.status_mult = params.default_status_mult;
  Checkhp();
  if (params.mana >= 20) {
    if (params.mana >= 40) {
    }
  }
}

void Mage::Receivedamage(const float damage, const int element,
                         const float status) {
  Creature::Receivedamage(damage, element, status);
}

void Mage::Checkhp() { Creature::Checkhp(); }

void Mage::Offence(const int choice) {
  switch (choice) {
    case 1:
      params.defence = 0.5;
      break;
    case 2:
      params.hp = min(params.hp + 50, params.hp_max);
      break;
    case 3:
      params.hp = min(params.hp + 80, params.hp_max);
      params.defence = 1.5;
      break;
    default:
      break;
      break;
  }
}

void Mage::Magic(Creature* const target) {
  target->Receivedamage(params.damage * params.damage_mult, params.element,
                     params.status * params.status_mult);
}