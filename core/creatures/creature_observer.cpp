#include "creature_observer.h"

void CreatureObserver::AddSubscriber(UIController* const subscriber) {
  subscribers_.push_back(subscriber);
}

void CreatureObserver::RemoveSubscriber(UIController* const subscriber) {
  std::erase(subscribers_, subscriber);
}

CreatureObserver::CreatureObserver() {}