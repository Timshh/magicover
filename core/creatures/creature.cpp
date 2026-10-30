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
  float hit = damage * params.defence;
  params.hp -= hit;
  observer_->CallAct(RenderActions::kTakedamage, id_, hit);
  switch (element) {
    case 1:
      params.flame += status * params.flame_resist;
      if (params.flame >= 50) {
        params.flame = 0;
        params.hp -= 100;
        observer_->CallAct(RenderActions::kOverload, id_, 1);
        observer_->CallAct(RenderActions::kTakedamage, id_, 100);
      }
      break;
    case 2:
      params.frost += status * params.frost_resist;
      if (params.frost >= 50) {
        params.frost = 0;
        params.hp -= 100;
        observer_->CallAct(RenderActions::kOverload, id_, 2);
        observer_->CallAct(RenderActions::kTakedamage, id_, 100);
      }
      break;
    case 3:
      params.dark += status * params.dark_resist;
      if (params.dark >= 50) {
        params.dark = 0;
        params.hp -= 100;
        observer_->CallAct(RenderActions::kOverload, id_, 3);
        observer_->CallAct(RenderActions::kTakedamage, id_, 100);
      }
      break;
    case 4:
      params.psycho += status * params.psycho_resist;
      if (params.psycho >= 50) {
        params.psycho = 0;
        params.hp -= 100;
        observer_->CallAct(RenderActions::kOverload, id_, 4);
        observer_->CallAct(RenderActions::kTakedamage, id_, 100);
      }
      break;
  }
  CheckHP();
}

void Creature::CheckHP() {
  if (!alive) {
    return;
  }
  if (params.hp <= 0) {
    observer_->CallAct(RenderActions::kDeath, id_);
    alive = false;
  }
}

void Creature::Act(Creature* const target) {
  if (!alive) {
    return;
  }
  params.hp -= params.flame;
  CheckHP();
}
