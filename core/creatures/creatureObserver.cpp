#include "creatureObserver.h"

void CreatureObserver::AddSubscriber(Renderer* subscriber) {
  Subscribers.push_back(subscriber);
}

void CreatureObserver::RemoveSubscriber(Renderer* subscriber) {
  std::erase(Subscribers, subscriber);
}

void CreatureObserver::CallAct(RenderActions action) {
  for (Renderer* renderer : Subscribers) {
    renderer->CallAct(action);
  }
}

CreatureObserver::CreatureObserver() {}