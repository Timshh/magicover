#include "boss.h"

Boss::Boss(CreatureStats params, std::vector<Creature*>* team,
           std::vector<Creature*>* enemies, int* maxenemies,
           ResourceManager* resmanager, Renderer* render)
    : Enemy(params, team, render) {

  Enemies = enemies;
  MaxEnemies = maxenemies;
  ResManager = resmanager;
  switch (Params.SpecAtkID) {
    case 1:
      Render->PrintMessage(8, "Two guardians of castle stand before Last Mage. One raise his "
             "heavy shield, another prepared "
             "battle axe. Fight is only "
             "option\n");
      break;
    case 3:
      Render->PrintMessage(
          8,
          "The palace smell dry. In center of it stands mummified witch "
          "corpse with eight arms. As Mage get closer she rise her gaze to "
          "Last Mage, her dead eyes glow red. This is mad witch who "
          "cheated death now known as ");
      Render->PrintMessage(4, "InfArmY");
      Render->PrintMessage(8, " - supreme ripper\n");
      break;
    case 4:
      Render->PrintMessage(8, "As Last Mage enter the palace, smoke fill it. As steam cleared, "
             "Gorgeous machine stood before Last Mage. ");
      Render->PrintMessage(14, "GO-13M. Greatest clockwork mechanism.");
      Render->PrintMessage(8, " It's a pity that such perfection is enemy of the Mage\n");
      Render->PrintMessage(12, "- Powerful treat detected. Starting battle\n ");
      break;
    case 6:
      Render->PrintMessage(8, "Gorgeous creature were watching in mosaic window as Last Mage "
             "appeared. It slowly turns to manifest itself. Thin legs levitate "
             "above ground, Halo shines with purple, Wings spread wide and "
             "separate from body, long "
             "tail curl around thin arm and purple core shine inside its "
             "chest. Round dark helmet hide its head. Creature look too weird "
             "to be a human. This is the final battle. Battle with\n");
      Render->PrintMessage(13, "TYRANT");
      Render->PrintMessage(8, " - the order creator and the first slayer\n");
      break;
  }
}

void Boss::SpecialAttack(Creature* target) {
  switch (Params.SpecAtkID) {
    case 1:
      Render->PrintMessage(15, "Shield guardian used heal potion - restored 20 health\n");
      Params.HP = min(Params.HP + 20, Params.HPMax);
      break;
    case 2:
      Render->PrintMessage(15, "Axe guardian looked at ring on his arm. His elemental statuses "
              "decreased slightly\n");
      Params.Flame = max(Params.Flame - 3, 0);
      Params.Frost = max(Params.Frost - 3, 0);
      Params.Dark = max(Params.Dark - 3, 0);
      Params.Psycho = max(Params.Psycho - 3, 0);
      break;
    case 3:
      if (Enemies->size() < *MaxEnemies) {
        Enemies->push_back(
            new Enemy(ResManager->GetCreature("Arms cluster"), Enemies, Render));
        Render->PrintMessage(15, "Witch created cluster of arms\n");
      } else {
        Render->PrintMessage(
            15, "Witch tried to create more arms but overloaded herself - 20 "
                "damage\n");
        Params.HP -= 20;
        CheckHP();
      }
      break;
    case 4:
      Render->PrintMessage(15, "Golem releases steam\n");
      Render->PrintMessage(12, "- Overheat. Processing...\n");
      break;
    case 5:
      std::cout
         , "Wings throw feathers around. Feathers decrease enemy statuses\n" ;
      for (Creature* boss : *Team) {
        boss->Params.Flame = max(boss->Params.Flame - 3, 0);
        boss->Params.Frost = max(boss->Params.Frost - 3, 0);
        boss->Params.Dark = max(boss->Params.Dark - 3, 0);
        boss->Params.Psycho = max(boss->Params.Psycho - 3, 0);
      }
      break;
    case 6:
      if (SpecFlag) {
        Render->PrintMessage(15, "Tyrant emits a mighty roar and strike with all limbs. ");
        float AtkDamage = (40 + rand() % (11)) * (1 - Params.Frost / 100) *
                          target->Params.Defence;
        Render->PrintMessage(15, "That inflict ", AtkDamage, " damage to Last Mage\n");
        target->Params.HP -= AtkDamage;
        SpecFlag = false;
      } else {
        Render->PrintMessage(15, "Tyrant prepares something, her core glow bright\n");
        SpecFlag = true;
      }
      break;
    case 7:
      Render->PrintMessage(15, "Halo shine with purple light. Light heal all enemies by 20 "
              "health\n");
      for (Creature* boss : *Team) {
        boss->Params.HP = min(boss->Params.HP + 20, boss->Params.HPMax);
      }
      break;
  }
}

void Boss::Act(Creature* target) {
  Params.HP -= Params.Flame;
  CheckHP();
  if (Alive) {
    if (rand() % 100 >= SpecAttackChance) {
      Attack(target);
    } else {
      SpecialAttack(target);
    }
  }
}

void Boss::CheckHP() {
  Enemy::CheckHP();
}