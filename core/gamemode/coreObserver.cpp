#include "coreObserver.h"

void CoreObserver::AddSubscriber(UIController* const subscriber) {
  Subscribers.push_back(subscriber);
}

void CoreObserver::RemoveSubscriber(UIController* const subscriber) {
  std::erase(Subscribers, subscriber);
}

void CoreObserver::CallAct(RenderActions const action) {
  for (UIController* renderer : Subscribers) {
    renderer->CallAct(action);
  }
}

CoreObserver::CoreObserver() {}