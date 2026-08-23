#include "coreObserver.h"

void CoreObserver::AddSubscriber(UIController* const subscriber) {
  Subscribers.push_back(subscriber);
}

void CoreObserver::RemoveSubscriber(UIController* const subscriber) {
  std::erase(Subscribers, subscriber);
}

void CoreObserver::CallAct(RenderActions const action, int ID, int params,
                           int subparams) {
  for (UIController* renderer : Subscribers) {
    renderer->CallAct(action, ID, params, subparams);
  }
}

CoreObserver::CoreObserver() {}