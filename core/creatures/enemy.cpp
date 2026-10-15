#include "enemy.h"

Enemy::Enemy(const CreatureStats params, std::vector<Creature*>* team,
             CoreObserver* const observer, const int id)
    : Creature(params, team, observer, id) {}

void Enemy::Act(Creature* target) {
  Creature::Act(target);
  if (alive) {
    Attack(target);
  }
}

void Enemy::Attack(Creature* target) {
  int Atkdamage = (params.damage + rand() % (params.damage_rand + 1)) *
                  (1 - params.frost / 100);
  if (rand() % 100 >= params.psycho) {
    if (rand() % 100 >= params.dark) {
      observer_->CallAct(RenderActions::kAttack, id_);
      target->Receivedamage(Atkdamage, 0, 0);
    } else {
    }
  } else {
    Receivedamage(Atkdamage, 0, 0);
  }
}

void Enemy::Status() {
  if (!this) {
    return;
  }
  Checkhp();
  if (params.hp >= params.hp_max / 2) {
  } else {
    if (params.hp >= params.hp_max / 4) {
    } else {
    }
  }
}

void Enemy::Receivedamage(const float damage, const int element,
                          const float status) {
  Creature::Receivedamage(damage, element, status);
}

void Enemy::Checkhp() {
  if (params.hp <= 0) {
  }
  Creature::Checkhp();
}