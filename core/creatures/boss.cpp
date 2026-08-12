#include "boss.h"

Boss::Boss(CreatureStats const params, std::vector<Creature*>* const team,
           std::vector<Creature*>* const enemies, int* const maxenemies,
           ResourceManager* const resmanager, CoreObserver* const observer,
           int const id)
    : Enemy(params, team, observer, id),
      Enemies(enemies),
      MaxEnemies(maxenemies),
      Manager(resmanager) {
  switch (Params.SpecAtkID) {
    case 1:
      break;
    case 3:
      break;
    case 4:
      break;
    case 6:
      break;
  }
}

void Boss::SpecialAttack(Creature* const target) {
  Observer->CallAct(RenderActions::SpecialAttack, ID);
  switch (Params.SpecAtkID) {
    case 1:
      Params.HP = min(Params.HP + 20, Params.HPMax);
      break;
    case 2:
      Params.Flame = max(Params.Flame - 3, 0);
      Params.Frost = max(Params.Frost - 3, 0);
      Params.Dark = max(Params.Dark - 3, 0);
      Params.Psycho = max(Params.Psycho - 3, 0);
      break;
    case 3:
      if (Enemies->size() < *MaxEnemies) {
        Enemies->push_back(
            new Enemy(Manager->GetCreature("Arms cluster"), Enemies, Observer, Enemies->size()));
      } else {
        Params.HP -= 20;
        CheckHP();
      }
      break;
    case 4:
      break;
    case 5:
      std::cout,
          "Wings throw feathers around. Feathers decrease enemy statuses\n";
      for (Creature* boss : *Team) {
        boss->Params.Flame = max(boss->Params.Flame - 3, 0);
        boss->Params.Frost = max(boss->Params.Frost - 3, 0);
        boss->Params.Dark = max(boss->Params.Dark - 3, 0);
        boss->Params.Psycho = max(boss->Params.Psycho - 3, 0);
      }
      break;
    case 6:
      if (SpecFlag) {
        float AtkDamage = (40 + rand() % (11)) * (1 - Params.Frost / 100) *
                          target->Params.Defence;
        target->Params.HP -= AtkDamage;
        SpecFlag = false;
      } else {
        SpecFlag = true;
      }
      break;
    case 7:
      for (Creature* boss : *Team) {
        boss->Params.HP = min(boss->Params.HP + 20, boss->Params.HPMax);
      }
      break;
  }
}

void Boss::Act(Creature* const target) {
  Params.HP -= Params.Flame;
  CheckHP();
  if (Alive) {
    if (rand() % 100 >= Params.SpecAtkChance) {
      Attack(target);
    } else {
      SpecialAttack(target);
    }
  }
}

void Boss::CheckHP() { Enemy::CheckHP(); }