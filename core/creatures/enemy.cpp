#include "enemy.h"

Enemy::Enemy(CreatureStats params, std::vector<Creature*>* team,
             CoreObserver* const observer, int const id)
    : Creature(params, team, observer, id) {}

void Enemy::Act(Creature* target) {
  Creature::Act(target);
  if (Alive) {
    Attack(target);
  }
}

void Enemy::Attack(Creature* target) {
  int AtkDamage = (Params.Damage + rand() % (Params.DamageRand + 1)) *
                  (1 - Params.Frost / 100);
  if (rand() % 100 >= Params.Psycho) {
    if (rand() % 100 >= Params.Dark) {
      Observer->CallAct(RenderActions::Attack, ID);
      target->ReceiveDmg(AtkDamage, 0, 0);
    } else {
    }
  } else {
    ReceiveDmg(AtkDamage, 0, 0);
  }
}

void Enemy::Status() {
  if (!this) {
    return;
  }
  CheckHP();
  if (Params.HP >= Params.HPMax / 2) {
  } else {
    if (Params.HP >= Params.HPMax / 4) {
    } else {
    }
  }
}

void Enemy::ReceiveDmg(float damage, int element, float status) {
  Creature::ReceiveDmg(damage, element, status);
}

void Enemy::CheckHP() {
  if (Params.HP <= 0) {
  }
  Creature::CheckHP();
}