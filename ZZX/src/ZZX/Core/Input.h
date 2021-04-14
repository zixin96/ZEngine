#pragma once

#include "ZZX/Core/Core.h"
#include "ZZX/Core/KeyCodes.h"
#include "ZZX/Core/MouseButtonCodes.h"

namespace ZZX
{
    class Input
    {
    public:
        static bool IsKeyPressed(KeyCode key);
        static bool IsMouseButtonPressed(MouseCode button);
        static std::pair<float, float> GetMousePosition();
        static float GetMouseX();
        static float GetMouseY();
    };
}