#include "creature.h"

Creature::Creature(CreatureStats const params,
                   std::vector<Creature*>* const team,
                   CoreObserver* const observer, int const id)
    : Params(params), Team(team), Observer(observer), ID(id) {}

void Creature::ReceiveDmg(float const damage, int const element,
                          float const status) {
  float Hit = damage * Params.Defence;
  Params.HP -= Hit;
  Observer->CallAct(RenderActions::TakeDamage, ID, Hit);
  switch (element) {
    case 1:
      Params.Flame += status * Params.FlameResist;
      if (Params.Flame >= 50) {
        Params.Flame = 0;
        Params.HP -= 100;
        Observer->CallAct(RenderActions::TakeDamage, ID, 100);
        //std::cout << "Flame overload! " << Params.Name << " exploded";
      }
      break;
    case 2:
      Params.Frost += status * Params.FrostResist;
      if (Params.Frost >= 50) {
        Params.Frost = 0;
        Params.HP -= 100;
        Observer->CallAct(RenderActions::TakeDamage, ID, 100);
        //std::cout << "Frost overload! " << Params.Name << " were frozen";
      }
      break;
    case 3:
      Params.Dark += status * Params.DarkResist;
      if (Params.Dark >= 50) {
        Params.Dark = 0;
        Params.HP -= 100;
        Observer->CallAct(RenderActions::TakeDamage, ID, 100);
        //std::cout << "Dark overload! " << Params.Name << " got corrupted";
      }
      break;
    case 4:
      Params.Psycho += status * Params.PsychoResist;
      if (Params.Psycho >= 50) {
        Params.Psycho = 0;
        Params.HP -= 100;
        Observer->CallAct(RenderActions::TakeDamage, ID, 100);
        //std::cout << "Psycho overload! " << Params.Name << " attacked self in hysteria";
      }
      break;
  }
  CheckHP();
}

void Creature::CheckHP() {
  if (Params.HP <= 0) {
    Alive = false;
  }
}

void Creature::Act(Creature* const target) {
  Params.HP -= Params.Flame;
  CheckHP();
}
