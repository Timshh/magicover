#include "mage.h"

void Mage::SetColor(int color) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, color);
}

Mage::Mage(CreatureStats params, std::vector<Creature*>* team)
    : Creature(params, team) {
}

void Mage::Act(Creature* target) {
  Creature::Act(target);
}

void Mage::Status() {
  Params.Mana = min(Params.Mana + 15, Params.ManaMax);
  for (Ring& currRing : Arm) {
    currRing.RingAct();
  }
  Params.Defence = Params.DefaultDefence;
  Params.DamageMult = Params.DefaultDamageMult;
  Params.StatusMult = Params.DefaultStatusMult;
  CheckHP();
  SetColor(11);
  std::cout << "\nLast Mage\n";
  SetColor(15);
  std::cout << "Health: ";
  SetColor(4);
  std::cout << Params.HP;
  SetColor(15);
  std::cout << " Mana: ";
  SetColor(3);
  std::cout << Params.Mana << "\n";
  SetColor(10);
  std::cout << Params.Poison << " ";
  SetColor(9);
  std::cout << Params.Disease << " ";
  SetColor(8);
  std::cout << Params.Mechanization << " ";
  SetColor(12);
  std::cout << Params.Stealer << std::endl;
  SetColor(15);
  std::cout << "1. Regenerate. Gain ";
  SetColor(3);
  std::cout << "15\n";
  SetColor(15);
  if (Params.Mana >= 20) {
    std::cout << "2. Support with spell. ";
    SetColor(3);
    std::cout << "20\n";
    SetColor(15);
    std::cout << "3. Attack with one element. ";
    SetColor(3);
    std::cout << "20\n";
    SetColor(15);
    if (Params.Mana >= 40) {
      std::cout << "4. Attack with two elements. ";
      SetColor(3);
      std::cout << "40\n";
      SetColor(15);
    }
  }
  std::cout << std::endl;
}

void Mage::RecieveDmg(float damage, int element, float status) {
  Creature::RecieveDmg(damage, element, status);
}

void Mage::CheckHP() {
  Creature::CheckHP();
}

void Mage::Offence() {
  int ChoiceElem;
  std::cout << "Choose spell:\n";
  std::cout << "1. Steel blood. Decrease incoming damage by half\n";
  std::cout << "2. Blue heart. Heal ";
  SetColor(4);
  std::cout << "50\n";
  SetColor(15);
  std::cout << "3. Radiance. Heal ";
  SetColor(4);
  std::cout << "80";
  SetColor(15);
  std::cout << " but incoming damage rise by half\n";
  std::cin >> ChoiceElem;
  system("cls");
  switch (ChoiceElem) {
    case 1:
      Params.Defence = 0.5;
      system("cls");
      std::cout << "Last mage blood became gray. His protction rise\n";
      break;
    case 2:
      Params.HP = min(Params.HP + 50, Params.HPMax);
      system("cls");
      std::cout
          << "Last Mage heart beat strong and slow, regenerating his health\n";
      break;
    case 3:
      Params.HP = min(Params.HP + 80, Params.HPMax);
      Params.Defence = 1.5;
      system("cls");
      std::cout
          << "Last Mage heart glow inside his chest, refilling his health. He "
             "is vulnerable now\n";
      break;
    default:
      system("cls");
      std::cout << "That didn't work\n";
      break;
      break;
  }
}

void Mage::Magic(Creature* target) {
  int ChoiceElem;
  std::cout << "Choose element:\n";
  std::cout << "1. Flame. Burn enemy slowly\n";
  std::cout << "2. Frost. Make enemy attacks weaker\n";
  std::cout << "3. Dark. With darken mind enemy may miss\n";
  std::cout << "4. Psycho. Enemy may lose control and attack self\n";
  std::cin >> ChoiceElem;
  switch (ChoiceElem) {
    case 1:
      Params.Damage = 20;
      Params.Status = 1;
      Params.Element = 1;
      break;
    case 2:
      Params.Damage = 25;
      Params.Status = 0.75;
      Params.Element = 2;
      break;
    case 3:
      Params.Damage = 15;
      Params.Status = 1.25;
      Params.Element = 3;
      break;
    case 4:
      Params.Damage = 10;
      Params.Status = 1.5;
      Params.Element = 4;
      break;
    default:
      system("cls");
      std::cout << "That didn't work\n";
      break;
      break;
  }
  system("cls");
  target->RecieveDmg(Params.Damage * Params.DamageMult, Params.Element,
                     Params.Status * Params.StatusMult);
}