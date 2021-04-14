#include "zzxpch.h"
#include "ZZX/Core/Input.h"

#include <GLFW/glfw3.h>
#include "ZZX/Core/Application.h"

namespace ZZX
{
    bool Input::IsKeyPressed(KeyCode keycode)
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        int state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::IsMouseButtonPressed(MouseCode button)
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        int state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    float Input::GetMouseX()
    {
        auto [x, y] = GetMousePosition();
        return x;
    }

    float Input::GetMouseY()
    {
        auto [x, y] = GetMousePosition();
        return y;
    }

    std::pair<float, float> Input::GetMousePosition()
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return { (float)xpos, (float)ypos };
    }
}
