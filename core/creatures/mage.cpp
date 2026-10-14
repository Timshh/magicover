#include "mage.h"

Mage::Mage(CreatureStats const params, std::vector<Creature*>* const team,
           CoreObserver* const observer, int const id)
    : Creature(params, team, observer, id) {}

void Mage::Act(Creature* const target) { Creature::Act(target); }

void Mage::Status() {
  params.Mana = min(params.Mana + 15, params.ManaMax);
  for (Ring& currRing : Arm) {
    currRing.RingAct();
  }
  params.Defence = params.DefaultDefence;
  params.DamageMult = params.DefaultDamageMult;
  params.StatusMult = params.DefaultStatusMult;
  CheckHP();
  if (params.Mana >= 20) {
    if (params.Mana >= 40) {
    }
  }
}

void Mage::ReceiveDamage(float const damage, int const element,
                      float const status) {
  Creature::ReceiveDamage(damage, element, status);
}

void Mage::CheckHP() { Creature::CheckHP(); }

void Mage::Offence(int const choice) {
  switch (choice) {
    case 1:
      params.Defence = 0.5;
      break;
    case 2:
      params.HP = min(params.HP + 50, params.HPMax);
      break;
    case 3:
      params.HP = min(params.HP + 80, params.HPMax);
      params.Defence = 1.5;
      break;
    default:
      break;
      break;
  }
}

void Mage::Magic(Creature* const target) {
  target->ReceiveDamage(params.Damage * params.DamageMult, params.Element,
                     params.Status * params.StatusMult);
}