#include "core_observer.h"

void CoreObserver::AddSubscriber(UIController* const subscriber) {
  subscribers_.push_back(subscriber);
}

void CoreObserver::RemoveSubscriber(UIController* const subscriber) {
  std::erase(subscribers_, subscriber);
}

void CoreObserver::CallAct(RenderActions const action, int id, int params,
                           int subparams) {
  for (UIController* renderer : subscribers_) {
    renderer->CallAct(action, id, params, subparams);
  }
}

CoreObserver::CoreObserver() {}