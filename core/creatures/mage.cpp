#include "mage.h"

Mage::Mage(CreatureStats const params, std::vector<Creature*>* const team,
           CoreObserver* const observer, int const id)
    : Creature(params, team, observer, id) {}

void Mage::Act(Creature* const target) { Creature::Act(target); }

void Mage::Status() {
  Params.Mana = min(Params.Mana + 15, Params.ManaMax);
  for (Ring& currRing : Arm) {
    currRing.RingAct();
  }
  Params.Defence = Params.DefaultDefence;
  Params.DamageMult = Params.DefaultDamageMult;
  Params.StatusMult = Params.DefaultStatusMult;
  CheckHP();
  if (Params.Mana >= 20) {
    if (Params.Mana >= 40) {
    }
  }
}

void Mage::ReceiveDmg(float const damage, int const element,
                      float const status) {
  Creature::ReceiveDmg(damage, element, status);
}

void Mage::CheckHP() { Creature::CheckHP(); }

void Mage::Offence(int const choice) {
  Observer->CallAct(RenderActions::SupportSpell, ID, choice);
  switch (choice) {
    case 1:
      Params.Defence = 0.5;
      break;
    case 2:
      Params.HP = min(Params.HP + 50, Params.HPMax);
      break;
    case 3:
      Params.HP = min(Params.HP + 80, Params.HPMax);
      Params.Defence = 1.5;
      break;
    default:
      break;
      break;
  }
}

void Mage::Magic(Creature* const target) {
  target->ReceiveDmg(Params.Damage * Params.DamageMult, Params.Element,
                     Params.Status * Params.StatusMult);
}