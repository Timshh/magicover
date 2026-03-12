#include "boss.h"

Boss::Boss(CreatureStats params, std::vector<Creature*>* team,
           std::vector<Creature*>* enemies, int* maxenemies,
           ResourceManager* resmanager, Renderer* render)
    : Enemy(params, team, render) {

  Enemies = enemies;
  MaxEnemies = maxenemies;
  ResManager = resmanager;
  switch (Params.ID) {
    case 1000:
      Render->PrintMessage(8, "Two guardians of castle stand before Last Mage. One raise his "
             "heavy shield, another prepared "
             "battle axe. Fight is only "
             "option\n");
      AtkText1 = "Shield guardian attack with shield";
      AtkText2 = "Shield guardian do a shield bash";
      AtkText3 = "Shield guardian slash with knife";
      AtkText4 = "Shield guardian throw small knife";
      CalmText = "Shield guardian stand still behind his shield";
      HurtText = "Shield guardian shake behind his shield";
      DamagedText =
          "Shield guardian barely stand, only shield don't let him fall";
      DeathText = "Shield guardian fell on knees breathless";
      Hint = "Shield guardian have resist to direct damage, but no more";
      break;
    case 1001:
      AtkText1 = "Axe guardian do a heavy slash";
      AtkText2 = "Axe guardian do two fast slashes";
      AtkText3 = "Axe guardian do a spin slash";
      AtkText4 = "Axe guardian attack with axe";
      CalmText = "Axe guardian look in Last Mage eyes";
      HurtText = "Axe guardian bleeds";
      DamagedText = "Axe guardian tries to stay focused";
      DeathText = "Axe guardian tried to attack. He fell before Last Mage";
      Hint =
          "Axe guardian have small resists to all elements. Looks like this is "
          "effect of his ring";
      break;
    case 1002:
      Render->PrintMessage(
          8,
          "The palace smell dry. In center of it stands mummified witch "
          "corpse with eight arms. As Mage get closer she rise her gaze to "
          "Last Mage, her dead eyes glow red. This is mad witch who "
          "cheated death now known as ");
      Render->PrintMessage(4, "InfArmY");
      Render->PrintMessage(8, " - supreme ripper\n");
      AtkText1 = "InfArmY attack with all her arms";
      AtkText2 = "Dead Witch deal multiple blows with her arms";
      AtkText3 = "Living corpse stand on arms and do fast kicks";
      AtkText4 = "Mummy create and throw auxiliary arm";
      CalmText = "InfArmY's arms sway in chaotic rhytm";
      HurtText = "Living Corpse bursts into laughter";
      DamagedText = "Witch shakes with malicious smile on her face";
      DeathText =
          "Mummy grab and rend herself apart spreading dust around, all her "
          "body and auxilary arms turned to dust";
      Hint =
          "Mad Witch have frost and dark resists, but flame works good against "
          "her mummyfied body. Madness make psycho effective against her";
      break;
    case 1003:
      Render->PrintMessage(8, "As Last Mage enter the palace, smoke fill it. As steam cleared, "
             "Gorgeous machine stood before Last Mage. ");
      Render->PrintMessage(14, "GO-13M. Greatest clockwork mechanism.");
      Render->PrintMessage(8, " It's a pity that such perfection is enemy of the Mage\n");
      Render->PrintMessage(12, "- Powerful treat detected. Starting battle\n ");
      AtkText1 = "GO-13M do a powerful kick";
      AtkText2 = "Machine rush towards Mage";
      AtkText3 = "Clockwork mechanism strike with high pressure steam";
      AtkText4 = "Mechanism strike with his arms";
      CalmText = "Machine click in perfect rhytm";
      HurtText = "GO-13M stand still";
      DamagedText = "Mechanism rhytm became unstable";
      DeathText = "GO-13M released lots of steam from spine";
      Hint =
          "Mechanical mind have strong psycho resist, also strong resist to "
          "direct attack damage. Good flame resist. Frost and dark are "
          "effective";
      break;
    case 1004:
      SpecAttackChance = 60;
      AtkText1 = "Wings strike with sharp feather";
      AtkText2 = "Wings do a spinnig attack";
      AtkText3 = "Wings strike with sharp feather";
      AtkText4 = "Wings do a spinnig attack";
      CalmText = "Wings fly near the Last Mage";
      HurtText = "Wings wave became unstable";
      DamagedText = "Wings shake in the air";
      DeathText = "Wings fell on ground";
      Hint =
          "Wings have small resist to direct damage. Elements are effective "
          "against it";
      break;
    case 1005:
      Render->PrintMessage(8, "Gorgeous creature were watching in mosaic window as Last Mage "
             "appeared. It slowly turns to manifest itself. Thin legs levitate "
             "above ground, Halo shines with purple, Wings spread wide and "
             "separate from body, long "
             "tail curl around thin arm and purple core shine inside its "
             "chest. Round dark helmet hide its head. Creature look too weird "
             "to be a human. This is the final battle. Battle with\n");
      Render->PrintMessage(13, "TYRANT");
      Render->PrintMessage(8, " - the order creator and the first slayer\n");
      AtkText1 = "Tyrant tail do a powerful stab";
      AtkText2 = "Creature fly towards mage and kick on full speeed";
      AtkText3 = "Thin arms strike with surprising power";
      AtkText4 = "The first slayer do multiples slashes with its tail";
      CalmText = "Creature slowly move up and down in air";
      HurtText = "Tyrant growl";
      DamagedText = "Helmet crack, it's growl rise";
      DeathText =
          "Tyrant helmet explode opening up a view of dark emptiness inside. "
          "Body fall on ground";
      Hint = "Tyrant have low resist to all elements and direct damage";
      break;
    case 1006:
      SpecAttackChance = 80;
      AtkText1 = "Halo strike with light";
      AtkText2 = "Halo attack with lightning";
      AtkText3 = "Halo strike with light";
      AtkText4 = "Halo attack with lightning";
      CalmText = "Halo shines with purple";
      HurtText = "Halo cracks";
      DamagedText = "Halo cracks shine white";
      DeathText = "Halo shine bright and slowly dissapear";
      Hint =
          "Halo have overresist to dark and psycho - they are useless. "
          "Anything else will be effective";
      break;
  }
}

void Boss::SpecialAttack(Creature* target) {
  switch (Params.ID) {
    case 1000:
      Render->PrintMessage(15, "Shield guardian used heal potion - restored 20 health\n");
      Params.HP = min(Params.HP + 20, Params.HPMax);
      break;
    case 1001:
      Render->PrintMessage(15, "Axe guardian looked at ring on his arm. His elemental statuses "
              "decreased slightly\n");
      Params.Flame = max(Params.Flame - 3, 0);
      Params.Frost = max(Params.Frost - 3, 0);
      Params.Dark = max(Params.Dark - 3, 0);
      Params.Psycho = max(Params.Psycho - 3, 0);
      break;
    case 1002:
      if (Enemies->size() < *MaxEnemies) {
        Enemies->push_back(new Enemy(ResManager->GetCreature(999), Enemies, Render));
        Render->PrintMessage(15, "Witch created cluster of arms\n");
      } else {
        Render->PrintMessage(
            15, "Witch tried to create more arms but overloaded herself - 20 "
                "damage\n");
        Params.HP -= 20;
        CheckHP();
      }
      break;
    case 1003:
      Render->PrintMessage(15, "Golem releases steam\n");
      Render->PrintMessage(12, "- Overheat. Processing...\n");
      break;
    case 1004:
      std::cout
         , "Wings throw feathers around. Feathers decrease enemy statuses\n";
      for (Creature* boss : *Team) {
        boss->Params.Flame = max(boss->Params.Flame - 3, 0);
        boss->Params.Frost = max(boss->Params.Frost - 3, 0);
        boss->Params.Dark = max(boss->Params.Dark - 3, 0);
        boss->Params.Psycho = max(boss->Params.Psycho - 3, 0);
      }
      break;
    case 1005:
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
    case 1006:
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