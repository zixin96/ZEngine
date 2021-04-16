#include "zzxpch.h"
#include "ZZX/Core/Input.h"

#include <GLFW/glfw3.h>
#include "ZZX/Core/Application.h"

namespace ZZX
{
    bool Input::IsKeyPressed(KeyCode keycode)
    {
        auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::IsMouseButtonPressed(MouseCode button)
    {
        auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    float Input::GetMouseX()
    {
		return GetMousePosition().x;
    }

    float Input::GetMouseY()
    {
		return GetMousePosition().y;
    }

    glm::vec2 Input::GetMousePosition()
    {
        auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return { (float)xpos, (float)ypos };
    }
}
