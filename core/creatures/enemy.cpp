#include "enemy.h"

Enemy::Enemy(CreatureStats params, std::vector<Creature*>* team,
             Renderer* render)
    : Creature(params, team, render) {
  /* switch (Params.ID) {
    case 0:
      AtkText1 = "Creature attack";
      AtkText2 = "It strikes";
      AtkText3 = AtkText1;
      AtkText4 = AtkText2;
      CalmText = "Patitent Zero don't move at all";
      HurtText = "Patitent Zero shake";
      DamagedText = "Patitent Zero shake stronger";
      DeathText = "Patitent Zero dissapeared";
      break;
    case 1:
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
      AtkText1 = "Slayer throw bunch of sharp spikes";
      AtkText2 = "Slayer throw big needles";
      AtkText3 = "Slayer throw strange sawblade";
      AtkText4 = "Slayer attack with sharp whip";
      CalmText = "Slayer joke at Last Mage";
      HurtText = "Slayer stay calm. Grin appears on his face";
      DamagedText = "Slayer eyes turned to dots";
      DeathText = "Slayer can't move. This is his last minutes";
      break;
    case 999:
      AtkText1 = "Arms cluster strike";
      AtkText2 = "Arms cluster roll towards Mage";
      AtkText3 = AtkText1;
      AtkText4 = AtkText2;
      CalmText = "Arms cluster move slowly";
      HurtText = "Arms cluster shake";
      DamagedText = "Arms cluster barely stand";
      DeathText = "Arms cluster fell to dust";
      break;
  }*/
}

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