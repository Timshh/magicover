#include "boss.h"

Boss::Boss(const CreatureStats params, std::vector<Creature*>* const team,
           std::vector<Creature*>* const enemies, int* const maxenemies,
           ResourceManager* const resmanager, CoreObserver* const observer,
           const int id)
    : Enemy(params, team, observer, id),
      enemies_(enemies),
      max_enemies_(maxenemies),
      manager_(resmanager) {}

void Boss::SpecialAttack(Creature* const target) {
  switch (params.spec_atk_id) {
    case 1:
      observer_->CallAct(RenderActions::kSpecialAttack, id_);
      params.hp = min(params.hp + 20, params.hp_max);
      break;
    case 2:
      observer_->CallAct(RenderActions::kSpecialAttack, id_);
      params.flame = max(params.flame - 3, 0);
      params.frost = max(params.frost - 3, 0);
      params.dark = max(params.dark - 3, 0);
      params.psycho = max(params.psycho - 3, 0);
      break;
    case 3:
      if (enemies_->size() < *max_enemies_) {
        observer_->CallAct(RenderActions::kSpecialAttack, id_);
        enemies_->push_back(new Enemy(manager_->GetCreature("Arms cluster"),
                                      enemies_, observer_, enemies_->size()));
      } else {
        observer_->CallAct(RenderActions::kSpecialAttack, id_, 1);
        Receivedamage(20, 0, 0);
        Checkhp();
      }
      break;
    case 4:
      observer_->CallAct(RenderActions::kSpecialAttack, id_);
      break;
    case 5:
      observer_->CallAct(RenderActions::kSpecialAttack, id_);
      for (Creature* boss : *team) {
        boss->params.flame = max(boss->params.flame - 3, 0);
        boss->params.frost = max(boss->params.frost - 3, 0);
        boss->params.dark = max(boss->params.dark - 3, 0);
        boss->params.psycho = max(boss->params.psycho - 3, 0);
      }
      break;
    case 6:
      if (spec_preparing_) {
        observer_->CallAct(RenderActions::kSpecialAttack, id_);
        float Atkdamage = (40 + rand() % (11)) * (1 - params.frost / 100) *
                          target->params.defence;
        target->Receivedamage(Atkdamage, 0, 0);
        spec_preparing_ = false;
      } else {
        observer_->CallAct(RenderActions::kAtkPreparing, id_);
        spec_preparing_ = true;
      }
      break;
    case 7:
      observer_->CallAct(RenderActions::kSpecialAttack, id_);
      for (Creature* boss : *team) {
        boss->params.hp = min(boss->params.hp + 20, boss->params.hp_max);
      }
      break;
  }
}

void Boss::Act(Creature* const target) {
  params.hp -= params.flame;
  Checkhp();
  if (alive) {
    if (spec_preparing_) {
      SpecialAttack(target);
    } else {
      if (rand() % 100 >= params.spec_atk_chance) {
        Attack(target);
      } else {
        SpecialAttack(target);
      }
    }
  }
}

void Boss::Checkhp() { Enemy::Checkhp(); }