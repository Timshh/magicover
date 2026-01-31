#include "boss.h"

float Boss::Clamp(float num, float min, float max) {
  if (num > max) {
    return max;
  }
  if (num < min) {
    return min;
  }
  return num;
}

Boss::Boss(int ID = 0) {
  Type = ID;
  IsBoss = 1;
  switch (Type) {
    case 0:
      SetColor(8);
      std::cout
          << "Two guardians of castle stand before Last Mage. One raise his "
             "heavy shield, another prepared "
             "battle axe. Fight is only "
             "option\n";
      SetColor(7);
      HP = HPMax = 100;
      Damage = 5;
      Resist = 0.6;
      DamageRand = 10;
      Name = "Shield guardian";
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
    case 1:
      HP = HPMax = 100;
      Damage = 10;
      DamageRand = 5;
      SpecAttackChance = 20;
      PsychoResist = 0.9;
      FlameResist = 0.9;
      FrostResist = 0.9;
      DarkResist = 0.9;
      Name = "Axe guardian";
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
    case 2:
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
      HP = HPMax = 300;
      Damage = 1;
      DamageRand = 39;
      PsychoResist = 1.4;
      FlameResist = 1.2;
      FrostResist = 0.8;
      DarkResist = 0.8;
      Name = "InfArmY";
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
    case 3:
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
      HP = HPMax = 400;
      Damage = 20;
      DamageRand = 20;
      SpecAttackChance = 40;
      Resist = 0.5;
      PsychoResist = 0.4;
      FlameResist = 0.8;
      FrostResist = 1.2;
      DarkResist = 1.2;
      Name = "GO-13M";
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
    case 4:
      HP = HPMax = 150;
      Damage = 5;
      DamageRand = 10;
      SpecAttackChance = 60;
      Resist = 0.9;
      PsychoResist = 1.2;
      FlameResist = 1.2;
      FrostResist = 1.2;
      DarkResist = 1.2;
      Name = "Wings";
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
    case 5:
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
      HP = HPMax = 300;
      Damage = 10;
      DamageRand = 20;
      SpecAttackChance = 30;
      Resist = 0.8;
      PsychoResist = 0.8;
      FlameResist = 0.8;
      FrostResist = 0.8;
      DarkResist = 0.8;
      Name = "Tyrant";
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
    case 6:
      HP = HPMax = 100;
      Damage = 2;
      DamageRand = 2;
      SpecAttackChance = 80;
      Resist = 1.2;
      PsychoResist = 0;
      FlameResist = 1.2;
      FrostResist = 1.2;
      DarkResist = 0;
      Name = "Halo";
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

void Boss::SpecialAttack(float* Defence,
                         int* NormalAdd,
                         int* MainHP, int* MaxEnemies, int* MaxStage,
    int* CurrentStage, int* CoordX, int* NormalRand,
    int* EliteAdd, int* EliteRand, int* CoordY, std::vector<int>* GetableRings,
    std::vector<Boss>* StageBosses, std::vector<Enemy>* Enemies, 
    std::vector<Ring>* Inventory, std::vector<std::vector<std::string>>* Map) {
  switch (Type) {
    case 0:
      std::cout << "Shield guardian used heal potion - restored 20 health\n";
      HP = Clamp(HP + 20, 0, HPMax);
      break;
    case 1:
      std::cout
          << "Axe guardian looked at ring on his arm. His elemental statuses "
              "decreased slightly\n";
      Flame = Clamp(Flame - 3, 0, 100);
      Frost = Clamp(Frost - 3, 0, 100);
      Dark = Clamp(Dark - 3, 0, 100);
      Psycho = Clamp(Psycho - 3, 0, 100);
      break;
    case 2:
      if (Enemies->size() < *MaxEnemies) {
        std::cout << "Witch created cluster of arms\n";
        Enemies->push_back(Enemy(0));
      } else {
        std::cout
            << "Witch tried to create more arms but overloaded herself - 20 "
                "damage\n";
        HP -= 20;
        CheckHP(MaxStage, CurrentStage, CoordX, NormalAdd, NormalRand, EliteAdd,
                EliteRand, CoordY, GetableRings, StageBosses, Enemies,
                Inventory, Map);
      }
      break;
    case 3:
      std::cout << "Golem releases steam\n";
      SetColor(12);
      std::cout << "- Overheat. Processing...\n";
      SetColor(7);
      break;
    case 4:
      std::cout
          << "Wings throw feathers around. Feathers decrease enemy statuses\n";
      for (Boss& boss : *StageBosses) {
        boss.Flame = Clamp(boss.Flame - 3, 0, 100);
        boss.Frost = Clamp(boss.Frost - 3, 0, 100);
        boss.Dark = Clamp(boss.Dark - 3, 0, 100);
        boss.Psycho = Clamp(boss.Psycho - 3, 0, 100);
      }
      break;
    case 5:
      if (SpecFlag) {
        std::cout << "Tyrant emits a mighty roar and strike with all limbs. ";
        float AtkDamage = (40 + rand() % (11)) * (1 - Frost / 100) * *Defence;
        std::cout << "That inflict " << AtkDamage << " damage to Last Mage\n";
        *MainHP -= AtkDamage;
        SpecFlag = false;
      } else {
        std::cout << "Tyrant prepares something, her core glow bright\n";
        SpecFlag = true;
      }
      break;
    case 6:
      std::cout << "Halo shine with purple light. Light heal all enemies by 20 "
              "health\n";
      for (Boss& boss : *StageBosses) {
        boss.HP = Clamp(boss.HP + 20, 0, boss.HPMax);
      }
      break;
  }
}

void Boss::Act(float* Defence, int* NormalAdd, int* MainHP, int* MaxEnemies,
               std::vector<Boss>* StageBosses, std::vector<Enemy>* Enemies,
               int* MaxStage, int* CurrentStage, int* CoordX,
               int* NormalRand, int* EliteAdd, int* EliteRand, int* CoordY,
               std::vector<int>* GetableRings,
               std::vector<Ring>* Inventory,
               std::vector<std::vector<std::string>>* Map) {
  HP -= Flame;
  CheckHP(MaxStage, CurrentStage, CoordX, NormalAdd, NormalRand, EliteAdd,
          EliteRand, CoordY, GetableRings, StageBosses, Enemies, Inventory,
          Map);
  if (rand() % 100 >= SpecAttackChance) {
    Attack(MainHP, Defence);
  } else {
    SpecialAttack(Defence, NormalAdd, MainHP, MaxEnemies, MaxStage,
                  CurrentStage, CoordX, NormalRand, EliteAdd, EliteRand, CoordY,
                  GetableRings, StageBosses, Enemies, Inventory, Map);
  }
}

void Boss::CheckHP(int* MaxStage, int* CurrentStage, int* CoordX, int* NormalAdd, int* NormalRand,
                   int* EliteAdd, int* EliteRand,
                   int* CoordY,  
                   std::vector<int>* GetableRings,
                   std::vector<Boss>* StageBosses, std::vector<Enemy>* Enemies,
                   std::vector<Ring>* Inventory,
                   std::vector < std::vector<std::string>>* Map) {
  if (HP <= 0) {
    std::cout << DeathText << "\n\n";
    Alive = false;
    std::erase_if(*StageBosses, [](const Boss& b) { return !b.Alive; });
    if (StageBosses->empty()) {
      if (!Enemies->empty()) {
        Enemies->clear();
      }
      switch (*CurrentStage) {
        case 0:
          std::cout << "Axe guardian ring shines bright\n";
          SetColor(2);
          std::cout << "Ring of memories obtained\n\n";
          Inventory->push_back(Ring(0));
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
          Inventory->push_back(Ring(888));
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
          Inventory->push_back(Ring(1834));
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
      *MaxStage++;
      *CurrentStage++;
    }
  }
}