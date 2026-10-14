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

Ring::Ring(RingStats stats, Creature* owner) : Stats(stats), Owner(owner) {}

void Ring::RingAct() {
  for (int i = 0; i < Stats.AEffects.size(); i++) {
    switch (Stats.AEffects[i]) {
      case 1:
        Owner->params.HP = Clamp(Owner->params.HP + 5, 0, Owner->params.HPMax);
        break;
      case 2:
        Owner->params.Mana =
            Clamp(Owner->params.Mana + 5, 0, Owner->params.ManaMax);
        break;
      case 3:
        Owner->params.HP =
            Clamp(Owner->params.HP + (rand() % int(Stats.AStats[i]) * 2) -
                      Stats.AStats[i] + 1,
                  0, Owner->params.HPMax);
        break;
      case 4:
        Owner->params.Mana =
            Clamp(Owner->params.Mana + rand() % (int(Stats.AStats[i]) * 2) -
                      Stats.AStats[i] + 1,
                  0, Owner->params.ManaMax);
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
        Owner->params.DefaultDefence += Stats.PStats[i] * Mult;
        break;
      case 2:
        Owner->params.HPMax += Stats.PStats[i] * Mult;
        Owner->params.HP = Clamp(Owner->params.HP, 0, Owner->params.HPMax);
        break;
      case 3:
        Owner->params.ManaMax += Stats.PStats[i] * Mult;
        Owner->params.Mana =
            Clamp(Owner->params.Mana, 0, Owner->params.ManaMax);
        break;
      case 4:
        Owner->params.SecondChance += Stats.PStats[i] * Mult;
        break;
      case 5:
        Owner->params.SecondAtkChance += Stats.PStats[i] * Mult;
        break;
      case 6:
        Owner->params.DefaultStatusMult += Stats.PStats[i] * Mult;
        break;
      case 7:
        Owner->params.DefaultDamageMult += Stats.PStats[i] * Mult;
        break;
    }
  }
}