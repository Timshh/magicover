#include "creatureObserver.h"

void CreatureObserver::AddSubscriber(UIController* const subscriber) {
  Subscribers.push_back(subscriber);
}

void CreatureObserver::RemoveSubscriber(UIController* const subscriber) {
  std::erase(Subscribers, subscriber);
}

void CreatureObserver::CallAct(RenderActions const action) {
  for (UIController* renderer : Subscribers) {
    renderer->CallAct(action);
  }
}

CreatureObserver::CreatureObserver() {}