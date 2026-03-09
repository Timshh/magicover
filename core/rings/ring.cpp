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

Ring::Ring(RingStats stats, Creature* owner) {
  Stats = stats;
  Owner = owner;
  switch (Stats.ID) {
    case 1:
      EquipText = "";
      UnequipText = "";
      break;
    case 2:
      EquipText = "";
      UnequipText = "";
      break;
    case 3:
      EquipText = "";
      UnequipText = "";
      break;
    case 4:
      EquipText = "";
      UnequipText = "";
      break;
    case 5:
      EquipText =
          "Strange, but instead of pain Last Mage feel hope. Hope, that he is "
          "the one who will finish with Order";
      UnequipText = "";
      break;
    case 6:
      EquipText = "";
      UnequipText = "";
      break;
    case 7:
      EquipText = "";
      UnequipText = "";
      break;
    case 8:
      EquipText = "";
      UnequipText = "";
      break;
    case 9:
      EquipText = "";
      UnequipText = "";
      break;
    case 10:
      EquipText = "";
      UnequipText = "";
      break;
    case 666:
      EquipText = "";
      UnequipText = "";
      break;
    case 0:
      EquipText = "";
      UnequipText = "";
      break;
    case 888:
      EquipText = "";
      UnequipText = "";
      break;
    case 1834:
      EquipText = "";
      UnequipText = "";
      break;
  }
}

void Ring::RingAct() {
  for (int i = 0; i < Stats.AEffects.size(); i++) {
    switch (Stats.AEffects[i]) {
      case 1:
        Owner->Params.HP = Clamp(Owner->Params.HP + 5, 0, Owner->Params.HPMax);
        break;
      case 2:
        Owner->Params.Mana =
            Clamp(Owner->Params.Mana + 5, 0, Owner->Params.ManaMax);
        break;
      case 3:
        Owner->Params.HP = Clamp(Owner->Params.HP + (rand() % int(Stats.AStats[i]) * 2) -
                      Stats.AStats[i] + 1,
                        0, Owner->Params.HPMax);
        break;
      case 4:
        Owner->Params.Mana = Clamp(Owner->Params.Mana + rand() % (int(Stats.AStats[i]) * 2) -
                      Stats.AStats[i] + 1,
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
  for (int i = 0; i < Stats.PEffects.size(); i++) {
    switch (Stats.PEffects[i]) {
      case 1:
        Owner->Params.DefaultDefence += Stats.PStats[i] * Mult;
        break;
      case 2:
        Owner->Params.HPMax += Stats.PStats[i] * Mult;
        Owner->Params.HP = Clamp(Owner->Params.HP, 0, Owner->Params.HPMax);
        break;
      case 3:
        Owner->Params.ManaMax += Stats.PStats[i] * Mult;
        Owner->Params.Mana =
            Clamp(Owner->Params.Mana, 0, Owner->Params.ManaMax);
        break;
      case 4:
        Owner->Params.SecondChance += Stats.PStats[i] * Mult;
        break;
      case 5:
        Owner->Params.SecondAtkChance += Stats.PStats[i] * Mult;
        break;
      case 6:
        Owner->Params.DefaultStatusMult += Stats.PStats[i] * Mult;
        break;
      case 7:
        Owner->Params.DefaultDamageMult += Stats.PStats[i] * Mult;
        break;
    }
  }
}