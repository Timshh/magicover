#include "creatureObserver.h"

void CreatureObserver::AddSubscriber(UIController* const subscriber) {
  Subscribers.push_back(subscriber);
}

void CreatureObserver::RemoveSubscriber(UIController* const subscriber) {
  std::erase(Subscribers, subscriber);
}

CreatureObserver::CreatureObserver() {}