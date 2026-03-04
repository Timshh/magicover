#include "ring.h"

float Ring::Clamp(float num, float min, float max) {
  if (num > max) {
    return max;
  }
  if (num < min) {
    return min;
  }
  return num;
}

Ring::Ring(int id, Creature* owner) {
  ID = id;
  Owner = owner;
  switch (ID) {
    case 1:
      Name = "Blue Blood ring";
      Description =
          "Deal low heal after turn.\nRing made with heart of Blue Mage, "
          "creator of BLue heart spell\n";
      EquipText = "";
      UnequipText = "";
      AEffects = {1};
      AStats = {4};
      break;
    case 2:
      Name = "Heart ring";
      Description =
          "Increase maximum health.\nOne of the first magical rings, created "
          "as gift with enough power to affect on Mages\n";
      EquipText = "";
      UnequipText = "";
      PEffects = {2};
      PStats = {25};
      break;
    case 3:
      Name = "Shiny ring";
      Description =
          "Increase maximal mana.\nRing which contains dawn light, was first "
          "ring created with calculated effect\n";
      EquipText = "";
      UnequipText = "";
      PEffects = {3};
      PStats = {25};
      break;
    case 4:
      Name = "Scaly ring";
      Description =
          "Increase defence.\nCreated with scales of draconic creature, one "
          "of the slayers to protect from next ones\n";
      EquipText = "";
      UnequipText = "";
      PEffects = {1};
      PStats = {0.2};
      break;
    case 5:
      Name = "Thorn ring";
      Description =
          "Deal damage after turn, but increase defence much\nRing with small "
          "thorns on it. Created out of despair by the one of the oldest Mages "
          "to fight with slayers, but which need blood to continue work\n";
      EquipText =
          "Strange, but instead of pain Last Mage feel hope. Hope, that he is "
          "the one who will finish with Order";
      UnequipText = "";
      PEffects = {1};
      PStats = {0.5};
      AEffects = {1};
      AStats = {-4};
      break;
    case 6:
      Name = "Light ring";
      Description =
          "Regenerate additional mana after turn.\nRing which absorbed one of "
          "the slayers light inside. This power slowly release in Mage who "
          "wears it, no one know it's limits\n";
      EquipText = "";
      UnequipText = "";
      AEffects = {2};
      AStats = {5};
      break;
    case 7:
      Name = "Fragile ring";
      Description =
          "Give one more chance. Once equipped, unequippable until mission "
          "will be ended.\nRegular ring on first look but any mage will feel "
          "it's power of ones who didn't survive the Slayers, their rage, "
          "their Hope\n";
      EquipText = "";
      UnequipText = "";
      PEffects = {4};
      PStats = {1};
      Uneqippable = false;
      break;
    case 8:
      Name = "Glass ring";
      Description =
          "Increase damage and status but lowers maximum health much.\nCreated "
          "by the selfish Mage who were sure that with enough power he wont "
          "get even one hit. The First Slayer destroyed him after dodging that "
          "Mage Attacks\n";
      EquipText = "";
      UnequipText = "";
      PEffects = {2, 6, 7};
      PStats = {-30, 0.25, 0.25};
      break;
    case 9:
      Name = "Unstable ring";
      Description =
          "After trun increase or decrease health.\nRing without only form. "
          "Were regular weak ring until Slayers tried to destroy it. It's "
          "power increased with ones who died in moment of release\n";
      EquipText = "";
      UnequipText = "";
      AEffects = {3};
      AStats = {5};
      break;
    case 10:
      Name = "Dice ring";
      Description =
          "Increase or decrease Mana after turn\nSix edged ring with numbers "
          "on it. Made by gambler mage when he "
          "lost all his money in game\n";
      EquipText = "";
      UnequipText = "";
      AEffects = {4};
      AStats = {5};
      break;
    case 666:
      Name = "Revengeance ring";
      Description =
          "Slightly increase all parameters\nPersonal ring of Last Mage, "
          "created with his blood\n";
      EquipText = "";
      UnequipText = "";
      PEffects = {1, 2, 3, 5, 6, 7};
      PStats = {0.05, 2, 2, 0.02, 0.1, 0.1};
      break;
    case 0:
      Name = "Ring of memories";
      Description =
          "Increase status dealt with attacks.\nRing with last words of best "
          "slayers. First it had low effect but with each new word it became "
          "stronger and stronger, filled with past of the bests. Looks like it "
          "were owned by one of Guardian relatives, one of the slayers\n";
      EquipText = "";
      UnequipText = "";
      PEffects = {6};
      PStats = {0.25};
      break;
    case 888:
      Name = "Ring of arms";
      Description =
          "Add chance to attack twice.\nA ring woven from red metallic arms, a "
          "deal Witch made to cheat the Death, the reason of her madness, but "
          "on Mage finger it works different\n";
      EquipText = "";
      UnequipText = "";
      PEffects = {5};
      PStats = {10};
      break;
    case 1834:
      Name = "Clockwork ring";
      Description =
          "Increase direct damage.\nOld mechanism which springs and gears "
          "still work like in day they were created. Clock in perfect rhytm, "
          "like the machine it were related to. First ring that work with "
          "mages but not made by them\n";
      EquipText = "";
      UnequipText = "";
      PEffects = {7};
      PStats = {0.5};
      break;
  }
}

void Ring::RingAct() {
  for (int i = 0; i < AEffects.size(); i++) {
    switch (AEffects[i]) {
      case 1:
        Owner->Params.HP = Clamp(Owner->Params.HP + 5, 0, Owner->Params.HPMax);
        break;
      case 2:
        Owner->Params.Mana =
            Clamp(Owner->Params.Mana + 5, 0, Owner->Params.ManaMax);
        break;
      case 3:
        Owner->Params.HP = Clamp(
            Owner->Params.HP + (rand() % int(AStats[i]) * 2) - AStats[i] + 1,
                        0, Owner->Params.HPMax);
        break;
      case 4:
        Owner->Params.Mana = Clamp(
            Owner->Params.Mana + rand() % (int(AStats[i]) * 2) - AStats[i] + 1,
            0,
                  Owner->Params.ManaMax);
        break;
    }
  }
}

void Ring::AddRingEffect(bool isRemoving) {
  int Mult = 1;
  if (isRemoving) {
    Mult = -1;
  }
  for (int i = 0; i < PEffects.size(); i++) {
    switch (PEffects[i]) {
      case 1:
        Owner->Params.DefaultDefence += PStats[i] * Mult;
        break;
      case 2:
        Owner->Params.HPMax += PStats[i] * Mult;
        Owner->Params.HP = Clamp(Owner->Params.HP, 0, Owner->Params.HPMax);
        break;
      case 3:
        Owner->Params.ManaMax += PStats[i] * Mult;
        Owner->Params.Mana =
            Clamp(Owner->Params.Mana, 0, Owner->Params.ManaMax);
        break;
      case 4:
        Owner->Params.SecondChance += PStats[i] * Mult;
        break;
      case 5:
        Owner->Params.SecondAtkChance += PStats[i] * Mult;
        break;
      case 6:
        Owner->Params.DefaultStatusMult += PStats[i] * Mult;
        break;
      case 7:
        Owner->Params.DefaultDamageMult += PStats[i] * Mult;
        break;
    }
  }
}