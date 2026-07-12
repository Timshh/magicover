#pragma once
#include <windows.h>

#include <cstdlib>
#include <iostream>

#include "renderData.h"

class Renderer {
 public:
  Renderer();
  void CallAct(RenderActions action);
};