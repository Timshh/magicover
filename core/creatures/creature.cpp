#include "creature.h"

Creature::Creature(CreatureStats const params,
                   std::vector<Creature*>* const team,
                   CoreObserver* const observer, const int id)
    : params(params), team(team), observer_(observer), id_(id) {}

void Creature::ReceiveDamage(const float damage, const int element,
                             const float status) {
  if (!alive) {
    return;
  }
  float Hit = damage * params.Defence;
  params.HP -= Hit;
  observer_->CallAct(RenderActions::TakeDamage, id_, Hit);
  switch (element) {
    case 1:
      params.Flame += status * params.FlameResist;
      if (params.Flame >= 50) {
        params.Flame = 0;
        params.HP -= 100;
        observer_->CallAct(RenderActions::Overload, id_, 1);
        observer_->CallAct(RenderActions::TakeDamage, id_, 100);
      }
      break;
    case 2:
      params.Frost += status * params.FrostResist;
      if (params.Frost >= 50) {
        params.Frost = 0;
        params.HP -= 100;
        observer_->CallAct(RenderActions::Overload, id_, 2);
        observer_->CallAct(RenderActions::TakeDamage, id_, 100);
      }
      break;
    case 3:
      params.Dark += status * params.DarkResist;
      if (params.Dark >= 50) {
        params.Dark = 0;
        params.HP -= 100;
        observer_->CallAct(RenderActions::Overload, id_, 3);
        observer_->CallAct(RenderActions::TakeDamage, id_, 100);
      }
      break;
    case 4:
      params.Psycho += status * params.PsychoResist;
      if (params.Psycho >= 50) {
        params.Psycho = 0;
        params.HP -= 100;
        observer_->CallAct(RenderActions::Overload, id_, 4);
        observer_->CallAct(RenderActions::TakeDamage, id_, 100);
      }
      break;
  }
  CheckHP();
}

void Creature::CheckHP() {
  if (!alive) {
    return;
  }
  if (params.HP <= 0) {
    observer_->CallAct(RenderActions::Death, id_);
    alive = false;
  }
}

void Creature::Act(Creature* const target) {
  if (!alive) {
    return;
  }
  params.HP -= params.Flame;
  CheckHP();
}
