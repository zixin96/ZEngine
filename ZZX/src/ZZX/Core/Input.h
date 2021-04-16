#pragma once

#include "ZZX/Core/KeyCodes.h"
#include "ZZX/Core/MouseButtonCodes.h"
#include <glm/glm.hpp>

namespace ZZX
{
	// to be implemented in platform-specific input class
    class Input
    {
    public:
        static bool IsKeyPressed(KeyCode key);
        static bool IsMouseButtonPressed(MouseCode button);
        static glm::vec2 GetMousePosition();
        static float GetMouseX();
        static float GetMouseY();
    };
}
