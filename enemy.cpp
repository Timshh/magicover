#include "enemy.h"

void Enemy::SetColor(int color) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, color);
}

Enemy::Enemy(int ID) {
  Type = ID;
  switch (Type) {
    case 0:
      Name = "Arms cluster";
      HP = HPMax = 20;
      Damage = 5;
      DamageRand = 10;
      PsychoResist = 0.5;
      FlameResist = 0.5;
      FrostResist = 0.5;
      DarkResist = 0.5;
      AtkText1 = "Arms cluster strike";
      AtkText2 = "Arms cluster roll towards Mage";
      AtkText3 = AtkText1;
      AtkText4 = AtkText2;
      CalmText = "Arms cluster move slowly";
      HurtText = "Arms cluster shake";
      DamagedText = "Arms cluster barely stand";
      DeathText = "Arms cluster fell to dust";
      break;

    case 1:
      Name = "Hunter";
      HP = HPMax = 50;
      Damage = 6;
      DamageRand = 8;
      Resist = 1;
      PsychoResist = 1;
      FlameResist = 1;
      FrostResist = 1;
      DarkResist = 1;
      AtkText1 = "Hunter shoot with crossbow";
      AtkText2 = "Hunter attack with sword";
      AtkText3 = "Hunter throw a knife";
      AtkText4 = AtkText1;
      CalmText = "Hunter stand still";
      HurtText = "Hunter walk aroung Last Mage";
      DamagedText = "Hunter barely stand";
      DeathText = "Hunter fell";
      break;
    case 2:
      Name = "Knight";
      HP = HPMax = 60;
      Damage = 10;
      DamageRand = 4;
      Resist = 0.8;
      PsychoResist = 1.5;
      FlameResist = 1.5;
      FrostResist = 1.5;
      DarkResist = 1.5;
      AtkText1 = "Knight slash with sword";
      AtkText2 = "Knight kick";
      AtkText3 = AtkText2;
      AtkText4 = AtkText1;
      CalmText = "Knight preapare to attack";
      HurtText = "Knight stand on place";
      DamagedText = "Knight cough loud. Blood appears on his visor";
      DeathText = "Hunter fell";
      break;
    case 3:
      Name = "Warrior student";
      HP = HPMax = 40;
      Damage = 3;
      DamageRand = 7;
      Resist = 0.8;
      PsychoResist = 2;
      FlameResist = 1.5;
      FrostResist = 1.5;
      DarkResist = 2;
      AtkText1 = "Warrior throw weak potion";
      AtkText2 = "Warrior throw training darts";
      AtkText3 = "Warrior slash with knife";
      AtkText4 = "Warrior stab with knife";
      CalmText = "Warrior student look nervous";
      HurtText = "Warrior student shocked by the pain";
      DamagedText = "Warrior student try to stay on legs";
      DeathText = "Warrior student dies";
      break;
    case 4:
      Name = "Demon";
      HP = HPMax = 60;
      Damage = 3;
      DamageRand = 10;
      Resist = 1.2;
      PsychoResist = 0.9;
      FlameResist = 0.9;
      FrostResist = 0.9;
      DarkResist = 0.9;
      AtkText1 = "Demon slash with his claws";
      AtkText2 = "Demon attack with his wings";
      AtkText3 = "Demon bash with his body";
      AtkText4 = "Demon shoot with his hot blood";
      CalmText = "Demon fly near Last Mage";
      HurtText = "Demon stand on ground";
      DamagedText = "Demon is very red";
      DeathText = "Demon burn untill dissapear";
      break;
    case 5:
      Name = "Pseudo-Witch";
      HP = HPMax = 40;
      Damage = 12;
      DamageRand = 4;
      Resist = 1.1;
      PsychoResist = 0.5;
      FlameResist = 0.5;
      FrostResist = 0.5;
      DarkResist = 0.5;
      AtkText1 = "Pseudo-Witch throw a potion";
      AtkText2 = "Pseudo-Witch use enchanted stick to create fireball";
      AtkText3 = AtkText2;
      AtkText4 = AtkText1;
      CalmText = "Pseudo-Witch look in Last Mage soul";
      HurtText = "Pseudo-Witch don't move. Don't even breathe";
      DamagedText = "Pseudo-Witch growl";
      DeathText = "Pseudo-Witch dissapeared";
      break;
    case 6:
      Name = "Pseudo-Mage";
      HP = HPMax = 60;
      Damage = 6;
      DamageRand = 10;
      Resist = 1.3;
      PsychoResist = 0.4;
      FlameResist = 0.4;
      FrostResist = 0.4;
      DarkResist = 0.4;
      AtkText1 = "Pseudo-Mage cast a spell";
      AtkText2 = "Pseudo-Mage use grimoire to cast ice spike";
      AtkText3 = AtkText2;
      AtkText4 = AtkText1;
      CalmText = "Pseudo-Mage look hollow";
      HurtText = "Pseudo-Mage don't bleed";
      DamagedText = "Pseudo-Mage is close";
      DeathText = "Pseudo-Mage dissipated";
      break;
    case 7:
      Name = "Automaton-Cleaner";
      HP = HPMax = 40;
      Damage = 6;
      DamageRand = 10;
      Resist = 0.6;
      PsychoResist = 0.5;
      FlameResist = 1.3;
      FrostResist = 1.3;
      DarkResist = 1;
      AtkText1 = "Automaton attack with sharp legs";
      AtkText2 = "Automaton shoot one of his claws";
      AtkText3 = AtkText2;
      AtkText4 = AtkText1;
      CalmText = "Automaton gears click";
      HurtText = "Automaton releases too much steam";
      DamagedText = "Automaton shake, it's gears can't take more";
      DeathText = "Automaton broke to small gears";
      break;
    case 8:
      Name = "Automaton-Dog";
      HP = HPMax = 50;
      Damage = 5;
      DamageRand = 15;
      Resist = 0.5;
      PsychoResist = 0.3;
      FlameResist = 1.5;
      FrostResist = 1.5;
      DarkResist = 1;
      AtkText1 = "Mechanical Dog do a strong bite";
      AtkText2 = "Automaton-Dog attack with clawed paws";
      AtkText3 = AtkText2;
      AtkText4 = AtkText1;
      CalmText = "Automaton stand still on metallic legs";
      HurtText = "Automaton bark to simulate anger";
      DamagedText = "Automaton gears breaking";
      DeathText = "Automaton-Dog gears stopped forever";
      break;
    case 9:
      Name = "Witch candidate";
      HP = HPMax = 60;
      Damage = 5;
      DamageRand = 20;
      Resist = 0.8;
      PsychoResist = 1;
      FlameResist = 1;
      FrostResist = 1;
      DarkResist = 1;
      AtkText1 = "Candidate throw potion";
      AtkText2 = "Witch cast weak spell of fire";
      AtkText3 = AtkText2;
      AtkText4 = AtkText1;
      CalmText = "Witch candidate smiles";
      HurtText = "Witch candidate smile became nothing";
      DamagedText = "Witch candidate eyes shake";
      DeathText =
          "Witch tried to throw potion but were too weak. Potion finished her";
      break;
    case 10:
      Name = "Automaton-Dragon";
      HP = HPMax = 50;
      Damage = 5;
      DamageRand = 15;
      Resist = 0.6;
      PsychoResist = 0.3;
      FlameResist = 0.4;
      FrostResist = 2;
      DarkResist = 2;
      AtkText1 = "Dragon attack with flame stream";
      AtkText2 = "Mechanical dragon attack with his legs";
      AtkText3 = AtkText2;
      AtkText4 = AtkText1;
      CalmText = "Automaton-Dragon ";
      HurtText = "";
      DamagedText = "";
      DeathText = "";
      break;

    case 20:
      Name = "Archer";
      HP = HPMax = 100;
      Damage = 15;
      DamageRand = 15;
      Resist = 1.25;
      PsychoResist = 1.25;
      FlameResist = 1.25;
      FrostResist = 1.25;
      DarkResist = 1.25;
      AtkText1 = "Archer shoot with bow";
      AtkText2 = "Archer shoot with crossbow";
      AtkText3 = "Archer shoot with compact crossbows";
      AtkText4 = "Archer shoot a burst with bow";
      CalmText = "Archer aim his bow";
      HurtText = "Archer keep his breath calm but his eyes show fear";
      DamagedText = "Archer look back. He want to flee";
      DeathText = "Archer tried to run away. His mind fell befory his body did";
      break;
    case 21:
      Name = "Draconic hunter";
      HP = HPMax = 130;
      Damage = 10;
      DamageRand = 10;
      Resist = 1.3;
      PsychoResist = 1;
      FlameResist = 0.7;
      FrostResist = 0.7;
      DarkResist = 1;
      AtkText1 = "Draconic hunter slash with spear";
      AtkText2 = "Draconic hunter hit with spear";
      AtkText3 = "Draconic hunter slash with claws";
      AtkText4 = "Draconic hunter throw a knife";
      CalmText = "Draconic hunter run around Last Mage";
      HurtText = "Draconic hunter walk around Last Mage";
      DamagedText = "Draconic hunter move slower";
      DeathText = "Draconic hunter fall";
      break;
    case 22:
      Name = "Armored knight";
      HP = HPMax = 120;
      Damage = 20;
      DamageRand = 5;
      Resist = 0.2;
      PsychoResist = 2.5;
      FlameResist = 2.5;
      FrostResist = 2.5;
      DarkResist = 2.5;
      AtkText1 = "Armored knight slash with heavy sword";
      AtkText2 = "Armored knight do a spin attack";
      AtkText3 = "Armored knight lunge towards Last Mage";
      AtkText4 = AtkText1;
      CalmText =
          "Armored knight stand still, with heavy armor he looks immovable";
      HurtText = "Armored knight breath hard inside his heavy armor";
      DamagedText = "Armored knight can't hide red stains under his armor";
      DeathText =
          "Armor stand still and silent. Knight inside won't move anymore";
      break;
    case 23:
      Name = "Automaton-Hunter";
      HP = HPMax = 100;
      Damage = 20;
      DamageRand = 5;
      Resist = 0.3;
      PsychoResist = 2;
      FlameResist = 2;
      FrostResist = 2;
      DarkResist = 1.5;
      AtkText1 = "Automaton-Hunter shoot sawblade";
      AtkText2 = "Automaton-Hunter shoot with heavy darts";
      AtkText3 = "Automaton-Hunter slash with sharp fingers";
      AtkText4 = "Automaton-Hunter stab with leg";
      CalmText = "Automaton-Hunter show nothing";
      HurtText = "Automaton-Hunter shake, it's gears damaged";
      DamagedText = "Automaton-Hunter don't fear death";
      DeathText =
          "Automaton-Hunter try to do it's last attack. His gears break one by "
          "one and gorgeous machine fall before Last Mage";
      break;
    case 24:
      Name = "Slayer candidate";
      HP = HPMax = 80;
      Damage = 10;
      DamageRand = 25;
      Resist = 0.8;
      PsychoResist = 1;
      FlameResist = 1.2;
      FrostResist = 1.2;
      DarkResist = 1.5;
      AtkText1 = "Candidate use enchanced staff to create lightning orb";
      AtkText2 = "Candidate throw random potions";
      AtkText3 = "Candidate stab with staff";
      AtkText4 = "Candidate use enchanced crossbow";
      CalmText = "Slayer candidate look nervous";
      HurtText = "Slayer candidate don't understand what's going on";
      DamagedText = "Slayer candidate is crying";
      DeathText = "Slayer candidate heart stops before he dies from injures";
      break;
    case 25:
      Name = "Slayer";
      HP = HPMax = 130;
      Damage = 20;
      DamageRand = 10;
      Resist = 0.9;
      PsychoResist = 1;
      FlameResist = 1.4;
      FrostResist = 1;
      DarkResist = 1.5;
      AtkText1 = "Slayer throw bunch of sharp spikes";
      AtkText2 = "Slayer throw big needles";
      AtkText3 = "Slayer throw strange sawblade";
      AtkText4 = "Slayer attack with sharp whip";
      CalmText = "Slayer joke at Last Mage";
      HurtText = "Slayer stay calm. Grin appears on his face";
      DamagedText = "Slayer eyes turned to dots";
      DeathText = "Slayer can't move. This is his last minutes";
      break;
  }
}

void Enemy::Act(int* MainHP, float* Defence, std::vector<Enemy>* Enemies) {
  HP -= Flame;
  CheckHP(Enemies);
  Attack(MainHP, Defence);
}

void Enemy::Attack(int* MainHP, float*Defence) {
  int AtkDamage = (Damage + rand() % (DamageRand + 1)) * (1 - Frost / 100);
  if (rand() % 100 >= Psycho) {
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
    if (rand() % 100 >= Dark) {
      std::cout << " which inflict " << AtkDamage * *Defence
           << " damage to "
              "Last Mage\n";
      *MainHP -= AtkDamage * *Defence;
    } else {
      std::cout << ". Miss\n";
    }
  } else {
    std::cout << Name << " in psychotic assault hurt self with "
         << AtkDamage * (Resist) << " damage\n";
    HP -= AtkDamage;
  }
}

void Enemy::Stats(std::vector<Enemy>* Enemies) {
  CheckHP(Enemies);
  if (HP >= HPMax / 2) {
    std::cout << CalmText;
  } else {
    if (HP >= HPMax / 4) {
      std::cout << HurtText;
    } else {
      std::cout << DamagedText;
    }
  }
  SetColor(12);
  std::cout << " " << Flame;
  SetColor(11);
  std::cout << " " << Frost;
  SetColor(8);
  std::cout << " " << Dark;
  SetColor(13);
  std::cout << " " << Psycho;
  SetColor(7);
  std::cout << std::endl;
}

void Enemy::RecieveDmg(float* Dmg, float* DamageMult, int* Element, float* Status, float* StatusMult,
                       std::vector<Enemy>* Enemies) {
  HP -= *Dmg * *DamageMult * Resist;
  std::cout << Name + " got hit - " << (*Dmg * *DamageMult * Resist)
            << " damage\n";
  switch (*Element) {
    case 1:
      Flame += *Status * *StatusMult * FlameResist;
      if (Flame >= 50) {
        Flame = 0;
        HP -= 100;
        std::cout << "Flame overload! " << Name << " exploded";
      }
      break;
    case 2:
      Frost += *Status * *StatusMult * FrostResist;
      if (Frost >= 50) {
        Frost = 0;
        HP -= 100;
        std::cout << "Frost overload! " << Name << " were frozen";
      }
      break;
    case 3:
      Dark += *Status * *StatusMult * DarkResist;
      if (Frost >= 50) {
        Frost = 0;
        HP -= 100;
        std::cout << "Dark overload! " << Name << " got corrupted";
      }
      break;
    case 4:
      Psycho += *Status * *StatusMult * PsychoResist;
      if (Frost >= 50) {
        Frost = 0;
        HP -= 100;
        std::cout << "Psycho overload! " << Name
                  << " attacked self in hysteria";
      }
      break;
  }
  CheckHP(Enemies);
}

void Enemy::CheckHP(std::vector<Enemy>* Enemies) {
  if (HP <= 0) {
    std::cout << DeathText << "\n";
    Alive = false;
    erase_if(*Enemies, [](const Enemy& b) { return !b.Alive; });
  }
}