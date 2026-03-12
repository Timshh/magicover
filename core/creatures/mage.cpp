#include "mage.h"

Mage::Mage(CreatureStats params, std::vector<Creature*>* team, Renderer* render)
    : Creature(params, team, render) {
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
  Render->PrintMessage(11, "\nLast Mage\n");
  Render->PrintMessage(15, "Health: ");
  Render->PrintMessage(4, Params.HP);
  Render->PrintMessage(15, " Mana: ");
  Render->PrintMessage(3, Params.Mana, "\n");
  Render->PrintMessage(10, Params.Poison, " ");
  Render->PrintMessage(9, Params.Disease, " ");
  Render->PrintMessage(8, Params.Mechanization, " ");
  Render->PrintMessage(12, Params.Stealer, "\n");
  Render->PrintMessage(15, "1. Regenerate. Gain ");
  Render->PrintMessage(3, "15\n");
  if (Params.Mana >= 20) {
    Render->PrintMessage(15, "2. Support with spell. ");
    Render->PrintMessage(3, "20\n");
    Render->PrintMessage(15, "3. Attack with one element. ");
    Render->PrintMessage(3, "20\n");
    if (Params.Mana >= 40) {
      Render->PrintMessage(15, "4. Attack with two elements. ");
      Render->PrintMessage(3, "40\n");
    }
  }
  Render->PrintMessage(15, "\n");
}

void Mage::ReceiveDmg(float damage, int element, float status) {
  Creature::ReceiveDmg(damage, element, status);
}

void Mage::CheckHP() {
  Creature::CheckHP();
}

void Mage::Offence() {
  int ChoiceElem;
  Render->PrintMessage(15, "Choose spell:\n");
  Render->PrintMessage(15, "1. Steel blood. Decrease incoming damage by half\n");
  Render->PrintMessage(15, "2. Blue heart. Heal ");
  Render->PrintMessage(4, "50\n");
  Render->PrintMessage(15, "3. Radiance. Heal ");
  Render->PrintMessage(4, "80");
  Render->PrintMessage(15, " but incoming damage rise by half\n");
  std::cin >> ChoiceElem;
  Render->CleanRender();
  switch (ChoiceElem) {
    case 1:
      Params.Defence = 0.5;
      Render->CleanRender();
      Render->PrintMessage(15, "Last mage blood became gray. His protction rise\n");
      break;
    case 2:
      Params.HP = min(Params.HP + 50, Params.HPMax);
      Render->CleanRender();
      Render->PrintMessage(
          15,
          "Last Mage heart beat strong and slow, regenerating his health\n");
      break;
    case 3:
      Params.HP = min(Params.HP + 80, Params.HPMax);
      Params.Defence = 1.5;
      Render->CleanRender();
      Render->PrintMessage(15, "Last Mage heart glow inside his chest, refilling his health. He "
             "is vulnerable now\n");
      break;
    default:
      Render->CleanRender();
      Render->PrintMessage(15, "That didn't work\n");
      break;
      break;
  }
}

void Mage::Magic(Creature* target) {
  int ChoiceElem;
  Render->PrintMessage(
      15,
      "Choose element:\n1. Flame. Burn enemy slowly\n2. Frost. Make enemy "
      "attacks weaker\n3. Dark. With darken mind enemy may miss\n4. Psycho. "
      "Enemy may lose control and attack self\n");
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
      Render->CleanRender();
      Render->PrintMessage(4, "That didn't work\n");
      break;
      break;
  }
  Render->CleanRender();
  target->ReceiveDmg(Params.Damage * Params.DamageMult, Params.Element,
                     Params.Status * Params.StatusMult);
}