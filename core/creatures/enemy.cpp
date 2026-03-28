#include "enemy.h"

Enemy::Enemy(CreatureStats params, std::vector<Creature*>* team,
             Renderer* render)
    : Creature(params, team, render) {}

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
    Render->PrintMessage(15, Params.AtkTexts[rand() % Params.AtkTexts.size()]);
    if (rand() % 100 >= Params.Dark) {
      Render->PrintMessage(15, " which inflict ", AtkDamage * target->Params.Defence,
                          " damage to Last Mage\n");
      target->Params.HP -= AtkDamage * target->Params.Defence;
    } else {
      Render->PrintMessage(15, ". Miss\n");
    }
  } else {
    Render->PrintMessage(15, Params.Name, " in psychotic assault hurt self with "
             , AtkDamage * (Params.Defence), " damage\n");
    Params.HP -= AtkDamage;
  }
}

void Enemy::Status() {
  if (!this) {
    return;
  }
  CheckHP();
  if (Params.HP >= Params.HPMax / 2) {
    Render->PrintMessage(15, Params.CalmText);
  } else {
    if (Params.HP >= Params.HPMax / 4) {
      Render->PrintMessage(15, Params.HurtText);
    } else {
      Render->PrintMessage(15, Params.DamagedText);
    }
  }
  Render->PrintMessage(12, " ", Params.Flame);
  Render->PrintMessage(11, " ", Params.Frost);
  Render->PrintMessage(8, " ", Params.Dark);
  Render->PrintMessage(13, " ", Params.Psycho);
  Render->PrintMessage(7, "\n");
}

void Enemy::ReceiveDmg(float damage, int element, float status) {
  Creature::ReceiveDmg(damage, element, status);
}

void Enemy::CheckHP() {
  if (Params.HP <= 0) {
    Render->PrintMessage(15, Params.DeathText, "\n");
  }
  Creature::CheckHP();
}