#include "ring.h"

float Ring::Clamp(const float num, const float min, const float max) {
  if (num > max) {
    return max;
  }
  if (num < min) {
    return min;
  }
  return num;
}

Ring::Ring(const RingStats stats, Creature* const owner)
    : stats(stats), owner_(owner) {}

void Ring::RingAct() {
  for (int i = 0; i < stats.active_effects.size(); i++) {
    switch (stats.active_effects[i]) {
      case 1:
        owner_->params.hp = Clamp(owner_->params.hp + 5, 0, owner_->params.hp_max);
        break;
      case 2:
        owner_->params.mana =
            Clamp(owner_->params.mana + 5, 0, owner_->params.mana_max);
        break;
      case 3:
        owner_->params.hp =
            Clamp(owner_->params.hp + (rand() % int(stats.active_stats[i]) * 2) -
                      stats.active_stats[i] + 1,
                  0, owner_->params.hp_max);
        break;
      case 4:
        owner_->params.mana =
            Clamp(owner_->params.mana + rand() % (int(stats.active_stats[i]) * 2) -
                      stats.active_stats[i] + 1,
                  0, owner_->params.mana_max);
        break;
    }
  }
}

void Ring::AddRingEffect(const bool is_removing) {
  int Mult = 1;
  if (is_removing) {
    Mult = -1;
  }
  for (int i = 0; i < stats.passive_effects.size(); i++) {
    switch (stats.passive_effects[i]) {
      case 1:
        owner_->params.default_defence += stats.passive_stats[i] * Mult;
        break;
      case 2:
        owner_->params.hp_max += stats.passive_stats[i] * Mult;
        owner_->params.hp = Clamp(owner_->params.hp, 0, owner_->params.hp_max);
        break;
      case 3:
        owner_->params.mana_max += stats.passive_stats[i] * Mult;
        owner_->params.mana =
            Clamp(owner_->params.mana, 0, owner_->params.mana_max);
        break;
      case 4:
        owner_->params.second_chance += stats.passive_stats[i] * Mult;
        break;
      case 5:
        owner_->params.second_atk_chance += stats.passive_stats[i] * Mult;
        break;
      case 6:
        owner_->params.default_status_mult += stats.passive_stats[i] * Mult;
        break;
      case 7:
        owner_->params.default_damage_mult += stats.passive_stats[i] * Mult;
        break;
    }
  }
}