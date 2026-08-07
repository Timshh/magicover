#include "enemy.h"

Enemy::Enemy(CreatureStats params, std::vector<Creature*>* team)
    : Creature(params, team) {}

void Enemy::Act(Creature* target) {
  Creature::Act(target);
  if (Alive) {
    Attack(target);
  }
}

void Enemy::Attack(Creature* target) {
  PersonalObserver.CallAct(RenderActions::Attack);
  int AtkDamage = (Params.Damage + rand() % (Params.DamageRand + 1)) *
                  (1 - Params.Frost / 100);
  if (rand() % 100 >= Params.Psycho) {
    if (rand() % 100 >= Params.Dark) {
      target->Params.HP -= AtkDamage * target->Params.Defence;
    } else {
    }
  } else {
    Params.HP -= AtkDamage;
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
  PersonalObserver.CallAct(RenderActions::TakeDamage);
  Creature::ReceiveDmg(damage, element, status);
}

void Enemy::CheckHP() {
  if (Params.HP <= 0) {
  }
  Creature::CheckHP();
}