#include "renderer.h"

Renderer::Renderer() {}

void Renderer::CallAct(RenderActions action) {
  switch (action) {
    case RenderActions::Attack:
      std::cout << "Attack!\n";
      break;
    case RenderActions::TakeDamage:
      std::cout << "Took damage!\n";
      break;
  }
}