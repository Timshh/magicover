#include "enemy.h"

Enemy::Enemy(CreatureStats params, std::vector<Creature*>* team,
             CoreObserver* const observer, int const id)
    : Creature(params, team, observer, id) {}

void Enemy::Act(Creature* target) {
  Creature::Act(target);
  if (alive) {
    Attack(target);
  }
}

void Enemy::Attack(Creature* target) {
  int AtkDamage = (params.Damage + rand() % (params.DamageRand + 1)) *
                  (1 - params.Frost / 100);
  if (rand() % 100 >= params.Psycho) {
    if (rand() % 100 >= params.Dark) {
      observer_->CallAct(RenderActions::Attack, id_);
      target->ReceiveDamage(AtkDamage, 0, 0);
    } else {
    }
  } else {
    ReceiveDamage(AtkDamage, 0, 0);
  }
}

void Enemy::Status() {
  if (!this) {
    return;
  }
  CheckHP();
  if (params.HP >= params.HPMax / 2) {
  } else {
    if (params.HP >= params.HPMax / 4) {
    } else {
    }
  }
}

void Enemy::ReceiveDamage(float damage, int element, float status) {
  Creature::ReceiveDamage(damage, element, status);
}

void Enemy::CheckHP() {
  if (params.HP <= 0) {
  }
  Creature::CheckHP();
}