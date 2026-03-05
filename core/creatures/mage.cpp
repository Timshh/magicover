#include "mage.h"

void Mage::SetColor(int color) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, color);
}

Mage::Mage(Stats params, std::vector<Creature*>* team)
    : Creature(params, team) {
}

void Mage::Act(Creature* target) {
  Creature::Act(target);
}

void Mage::Attack(Creature* target) {
  int AtkDamage = (Params.Damage + rand() % (Params.DamageRand + 1)) *
                  (1 - Params.Frost / 100);
  if (rand() % 100 >= Params.Psycho) {
    if (rand() % 2 == 0) {
      if (rand() % 2 == 0) {
        std::cout << AtkText1;
      } else {
        std::cout << AtkText2;
      }
    } else {
      if (rand() % 2 == 0) {
        std::cout << AtkText3;
      } else {
        std::cout << AtkText4;
      }
    }
    if (rand() % 100 >= Params.Dark) {
      std::cout << " which inflict " << AtkDamage * target->Params.Defence
           << " damage to "
              "Last Mage\n";
      target->Params.HP -= AtkDamage * target->Params.Defence;
    } else {
      std::cout << ". Miss\n";
    }
  } else {
    std::cout << Params.Name << " in psychotic assault hurt self with "
              << AtkDamage * (Params.Defence) << " damage\n";
    Params.HP -= AtkDamage;
  }
}

void Mage::Status() {
  if (!this) {
    return;
  }
  CheckHP();
  if (Params.HP >= Params.HPMax / 2) {
    std::cout << CalmText;
  } else {
    if (Params.HP >= Params.HPMax / 4) {
      std::cout << HurtText;
    } else {
      std::cout << DamagedText;
    }
  }
  SetColor(12);
  std::cout << " " << Params.Flame;
  SetColor(11);
  std::cout << " " << Params.Frost;
  SetColor(8);
  std::cout << " " << Params.Dark;
  SetColor(13);
  std::cout << " " << Params.Psycho;
  SetColor(7);
  std::cout << std::endl;
}

void Mage::RecieveDmg(float damage, int element, float status) {
  Creature::RecieveDmg(damage, element, status);
}

void Mage::CheckHP() {
  if (Params.HP <= 0) {
    std::cout << DeathText << "\n";
  }
  Creature::CheckHP();
}