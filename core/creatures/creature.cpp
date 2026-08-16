#include "creature.h"

Creature::Creature(CreatureStats const params,
                   std::vector<Creature*>* const team,
                   CoreObserver* const observer, int const id)
    : Params(params), Team(team), Observer(observer), ID(id) {}

void Creature::ReceiveDmg(float const damage, int const element,
                          float const status) {
  if (!Alive) {
    return;
  }
  float Hit = damage * Params.Defence;
  Params.HP -= Hit;
  Observer->CallAct(RenderActions::TakeDamage, ID, Hit);
  switch (element) {
    case 1:
      Params.Flame += status * Params.FlameResist;
      if (Params.Flame >= 50) {
        Params.Flame = 0;
        Params.HP -= 100;
        Observer->CallAct(RenderActions::Overload, ID, 1);
        Observer->CallAct(RenderActions::TakeDamage, ID, 100);
      }
      break;
    case 2:
      Params.Frost += status * Params.FrostResist;
      if (Params.Frost >= 50) {
        Params.Frost = 0;
        Params.HP -= 100;
        Observer->CallAct(RenderActions::Overload, ID, 2);
        Observer->CallAct(RenderActions::TakeDamage, ID, 100);
      }
      break;
    case 3:
      Params.Dark += status * Params.DarkResist;
      if (Params.Dark >= 50) {
        Params.Dark = 0;
        Params.HP -= 100;
        Observer->CallAct(RenderActions::Overload, ID, 3);
        Observer->CallAct(RenderActions::TakeDamage, ID, 100);
      }
      break;
    case 4:
      Params.Psycho += status * Params.PsychoResist;
      if (Params.Psycho >= 50) {
        Params.Psycho = 0;
        Params.HP -= 100;
        Observer->CallAct(RenderActions::Overload, ID, 4);
        Observer->CallAct(RenderActions::TakeDamage, ID, 100);
      }
      break;
  }
  CheckHP();
}

void Creature::CheckHP() {
  if (!Alive) {
    return;
  }
  if (Params.HP <= 0) {
    Observer->CallAct(RenderActions::Death, ID);
    Alive = false;
  }
}

void Creature::Act(Creature* const target) {
  if (!Alive) {
    return;
  }
  Params.HP -= Params.Flame;
  CheckHP();
}
