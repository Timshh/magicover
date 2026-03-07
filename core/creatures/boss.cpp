#include "boss.h"

Boss::Boss(CreatureStats params, std::vector<Creature*>* team, int* maxEnemies,
           std::vector<Creature*>* enemies, int* maxStage, int* currentStage,
           int* coordX, int* coordY, int* normalAdd, int* normalRand,
           int* eliteAdd, int* eliteRand, std::vector<int>* getableRings,
           std::vector<Ring>* inventory,
           std::vector<std::vector<std::string>>* map, ResourceManager* manager,
           Creature* player)
    : Enemy(params, team) {
  MaxEnemies = maxEnemies;
  MaxStage = maxStage;
  CurrentStage = currentStage;
  CoordX = coordX;
  CoordY = coordY;
  NormalAdd = normalAdd;
  NormalRand = normalRand;
  EliteAdd = eliteAdd;
  EliteRand = eliteRand;
  Enemies = enemies;
  GetableRings = getableRings;
  Inventory = inventory;
  Map = map;
  EnemyManager = manager;
  Player = player;
  switch (Params.ID) {
    case 1000:
      SetColor(8);
      std::cout
          << "Two guardians of castle stand before Last Mage. One raise his "
             "heavy shield, another prepared "
             "battle axe. Fight is only "
             "option\n";
      SetColor(7);
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
      SetColor(8);
      std::cout
          << "The palace smell dry. In center of it stands mummified witch "
             "corpse with eight arms. As Mage get closer she rise her gaze to "
             "Last Mage, her dead eyes glow red. This is mad witch who "
             "cheated death now known as ";
      SetColor(4);
      std::cout << "InfArmY";
      SetColor(8);
      std::cout << " - supreme ripper\n";
      SetColor(7);
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
      SetColor(8);
      std::cout
          << "As Last Mage enter the palace, smoke fill it. As steam cleared, "
             "Gorgeous machine stood before Last Mage. ";
      SetColor(14);
      std::cout << "GO-13M. Greatest clockwork mechanism.";
      SetColor(8);
      std::cout << " It's a pity that such perfection is enemy of the Mage\n";
      SetColor(12);
      std::cout << "- Powerful treat detected. Starting battle\n ";
      SetColor(7);
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
      SetColor(8);
      std::cout
          << "Gorgeous creature were watching in mosaic window as Last Mage "
             "appeared. It slowly turns to manifest itself. Thin legs levitate "
             "above ground, Halo shines with purple, Wings spread wide and "
             "separate from body, long "
             "tail curl around thin arm and purple core shine inside its "
             "chest. Round dark helmet hide its head. Creature look too weird "
             "to be a human. This is the final battle. Battle with\n";
      SetColor(13);
      std::cout << "TYRANT";
      SetColor(8);
      std::cout << " - the order creator and the first slayer\n";
      SetColor(7);
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
      std::cout << "Shield guardian used heal potion - restored 20 health\n";
      Params.HP = min(Params.HP + 20, Params.HPMax);
      break;
    case 1001:
      std::cout
          << "Axe guardian looked at ring on his arm. His elemental statuses "
              "decreased slightly\n";
      Params.Flame = max(Params.Flame - 3, 0);
      Params.Frost = max(Params.Frost - 3, 0);
      Params.Dark = max(Params.Dark - 3, 0);
      Params.Psycho = max(Params.Psycho - 3, 0);
      break;
    case 1002:
      if (Enemies->size() < *MaxEnemies) {
        std::cout << "Witch created cluster of arms\n";
        Enemies->push_back(new Enemy(EnemyManager->GetCreature(999), Enemies));
      } else {
        std::cout
            << "Witch tried to create more arms but overloaded herself - 20 "
                "damage\n";
        Params.HP -= 20;
        CheckHP();
      }
      break;
    case 1003:
      std::cout << "Golem releases steam\n";
      SetColor(12);
      std::cout << "- Overheat. Processing...\n";
      SetColor(7);
      break;
    case 1004:
      std::cout
          << "Wings throw feathers around. Feathers decrease enemy statuses\n";
      for (Creature* boss : *Team) {
        boss->Params.Flame = max(boss->Params.Flame - 3, 0);
        boss->Params.Frost = max(boss->Params.Frost - 3, 0);
        boss->Params.Dark = max(boss->Params.Dark - 3, 0);
        boss->Params.Psycho = max(boss->Params.Psycho - 3, 0);
      }
      break;
    case 1005:
      if (SpecFlag) {
        std::cout << "Tyrant emits a mighty roar and strike with all limbs. ";
        float AtkDamage = (40 + rand() % (11)) * (1 - Params.Frost / 100) *
                          target->Params.Defence;
        std::cout << "That inflict " << AtkDamage << " damage to Last Mage\n";
        target->Params.HP -= AtkDamage;
        SpecFlag = false;
      } else {
        std::cout << "Tyrant prepares something, her core glow bright\n";
        SpecFlag = true;
      }
      break;
    case 1006:
      std::cout << "Halo shine with purple light. Light heal all enemies by 20 "
              "health\n";
      for (Creature* boss : *Team) {
        boss->Params.HP = min(boss->Params.HP + 20, boss->Params.HPMax);
      }
      break;
  }
}

void Boss::Act(Creature* target) {
  Params.HP -= Params.Flame;
  CheckHP();
  if (rand() % 100 >= SpecAttackChance) {
    Attack(target);
  } else {
    SpecialAttack(target);
  }
}

void Boss::CheckHP() {
  if (Params.HP <= 0) {
    std::cout << DeathText << "\n\n";
    Alive = false;
    std::erase_if(*Team, [](const Creature* b) { return !b->Alive; });

    // TEMP
    if (Team->empty()) {
      if (!Enemies->empty()) {
        Enemies->clear();
      }
      switch (*CurrentStage) {
        case 0:
          std::cout << "Axe guardian ring shines bright\n";
          SetColor(2);
          std::cout << "Ring of memories obtained\n\n";
          Inventory->push_back(Ring(0, Player));
          SetColor(7);
          std::cout << "Spacious outer palaces look regular";
          *CoordX = 0, *CoordY = 3;
          *EliteAdd = 20;
          *EliteRand = 2;
          *NormalAdd = 1;
          *NormalRand = 4;
          *Map = {
              {"  ", "  ", "  ", "  ", "  "},   {"  ", "P-", "M-", "R ", "  "},
              {" /", "  ", " \\", " \\", "  "}, {"S-", "E-", "R-", "M-", "B "},
              {" \\", " /", " /", "  ", "  "},  {"  ", "R-", "P ", "  ", "  "},
              {"  ", "  ", "  ", "  ", "  "}};
          break;
        case 1:
          std::cout << "Ring shines in the dust\n";
          SetColor(2);
          std::cout << "Ring of arms obtained\n\n";
          Inventory->push_back(Ring(888, Player));
          SetColor(7);
          std::cout << "Grandiose inner palaces shine before Last Mage";
          *CoordX = 0, *CoordY = 7;
          *EliteAdd = 21;
          *EliteRand = 4;
          *NormalAdd = 2;
          *NormalRand = 5;
          GetableRings->push_back(5);
          GetableRings->push_back(6);
          GetableRings->push_back(7);
          GetableRings->push_back(8);
          *Map = {
              {"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
              {"  ", "  ", "  ", "P-", "R-", "R-", "R", "  ", "  ", "  "},
              {"  ", "  ", " /", "  ", " \\", " \\", " \\", "  ", "  ", "  "},
              {"  ", "  ", "R-", "R-", "E-", "R-", "M-", "R ", "  ", "  "},
              {"  ", " /", "  ", "  ", "  ", " /", "  ", " \\", "  ", "  "},
              {"  ", "P-", "M ", "  ", "  ", "R-", "E ", "  ", "R ", "  "},
              {" /", "  ", " \\", "  ", " /", "  ", " \\", "  ", " \\", "  "},
              {"S-", "E-", "R-", "P-", "P ", "  ", "E-", "R-", "R-", "B "},
              {" \\", " /", " /", "  ", " \\", " /", " /", "  ", " /", "  "},
              {"  ", "R-", "P ", "  ", "  ", "M-", "R ", "  ", "R  ", "  "},
              {"  ", " \\", "  ", "  ", "  ", "  ", "  ", " /", "  ", "  "},
              {"  ", "  ", "M ", "  ", "E-", "P-", "M-", "R ", "  ", "  "},
              {"  ", "  ", " \\", " /", "  ", " \\", " /", "  ", "  ", "  "},
              {"  ", "  ", "  ", "E-", "R-", "E-", "R ", "  ", "  ", "  "},
              {"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "}};
          break;
        case 2:
          SetColor(12);
          std::cout << "- Overheat! Overheat! Overheat...\n";
          SetColor(7);
          std::cout
              << "As machine turned off, its chest opened. Inside was a ring\n";
          SetColor(2);
          std::cout << "Clockwork ring obtained\n\n";
          Inventory->push_back(Ring(1834, Player));
          SetColor(7);
          std::cout << "Slayers section feels majestically.Soon it will burn";
          *CoordX = 0, *CoordY = 5;
          *EliteAdd = 23;
          *EliteRand = 3;
          *NormalAdd = 5;
          *NormalRand = 5;
          GetableRings->push_back(9);
          GetableRings->push_back(10);
          *Map = {{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
                 {"  ", "  ", "P-", "E-", "M-", "R ", "  ", "  "},
                 {"  ", " /", "  ", "  ", " \\", " \\", "  ", "  "},
                 {"  ", "P-", "E-", "R ", "  ", "P-", "E ", "  "},
                 {" /", "  ", "  ", " \\", " /", "  ", " \\", "  "},
                 {"S-", "E-", "R-", "M-", "P ", "  ", "P-", "B "},
                 {" \\", "  ", " /", " \\", " \\", " /", " /", "  "},
                 {"  ", "R-", "P ", "  ", "P ", "M ", "R ", "  "},
                 {"  ", "  ", "  ", "  ", " \\", " /", "  ", "  "},
                 {"  ", "  ", "  ", "  ", "  ", "R ", "  ", "  "},
                 {"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "}};
          break;
        case 3:
          SetColor(10);
          std::cout
              << "\nYou finished the mission - you destroyed the order's core\n"
                 "Congratulations, Last Mage\n\n\n";
          SetColor(7);
          exit(0);
      }
      *MaxStage += 1;
      *CurrentStage += 1;
    }
  }
}