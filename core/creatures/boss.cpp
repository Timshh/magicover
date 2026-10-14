#include "boss.h"

Boss::Boss(CreatureStats const params, std::vector<Creature*>* const team,
           std::vector<Creature*>* const enemies, int* const maxenemies,
           ResourceManager* const resmanager, CoreObserver* const observer,
           int const id)
    : Enemy(params, team, observer, id),
      Enemies(enemies),
      MaxEnemies(maxenemies),
      Manager(resmanager) {}

void Boss::SpecialAttack(Creature* const target) {
  switch (params.SpecAtkID) {
    case 1:
      observer_->CallAct(RenderActions::SpecialAttack, id_);
      params.HP = min(params.HP + 20, params.HPMax);
      break;
    case 2:
      observer_->CallAct(RenderActions::SpecialAttack, id_);
      params.Flame = max(params.Flame - 3, 0);
      params.Frost = max(params.Frost - 3, 0);
      params.Dark = max(params.Dark - 3, 0);
      params.Psycho = max(params.Psycho - 3, 0);
      break;
    case 3:
      if (Enemies->size() < *MaxEnemies) {
        observer_->CallAct(RenderActions::SpecialAttack, id_);
        Enemies->push_back(new Enemy(Manager->GetCreature("Arms cluster"),
                                     Enemies, observer_, Enemies->size()));
      } else {
        observer_->CallAct(RenderActions::SpecialAttack, id_, 1);
        ReceiveDamage(20, 0, 0);
        CheckHP();
      }
      break;
    case 4:
      observer_->CallAct(RenderActions::SpecialAttack, id_);
      break;
    case 5:
      observer_->CallAct(RenderActions::SpecialAttack, id_);
      for (Creature* boss : *team) {
        boss->params.Flame = max(boss->params.Flame - 3, 0);
        boss->params.Frost = max(boss->params.Frost - 3, 0);
        boss->params.Dark = max(boss->params.Dark - 3, 0);
        boss->params.Psycho = max(boss->params.Psycho - 3, 0);
      }
      break;
    case 6:
      if (SpecFlag) {
        observer_->CallAct(RenderActions::SpecialAttack, id_);
        float AtkDamage = (40 + rand() % (11)) * (1 - params.Frost / 100) *
                          target->params.Defence;
        target->ReceiveDamage(AtkDamage, 0, 0);
        SpecFlag = false;
      } else {
        observer_->CallAct(RenderActions::AtkPreparing, id_);
        SpecFlag = true;
      }
      break;
    case 7:
      observer_->CallAct(RenderActions::SpecialAttack, id_);
      for (Creature* boss : *team) {
        boss->params.HP = min(boss->params.HP + 20, boss->params.HPMax);
      }
      break;
  }
}

void Boss::Act(Creature* const target) {
  params.HP -= params.Flame;
  CheckHP();
  if (alive) {
    if (SpecFlag) {
      SpecialAttack(target);
    } else {
      if (rand() % 100 >= params.SpecAtkChance) {
        Attack(target);
      } else {
        SpecialAttack(target);
      }
    }
  }
}

void Boss::CheckHP() { Enemy::CheckHP(); }