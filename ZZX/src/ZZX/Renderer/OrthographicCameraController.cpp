#include "zzxpch.h"
#include "OrthographicCameraController.h"
#include "ZZX/Core/Input.h"
#include "ZZX/Core/KeyCodes.h"

namespace ZZX
{
    
    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
        : m_AsepctRatio(aspectRatio), 
        m_ZoomLevel(1.0f), 
        m_Rotation(rotation), 
        m_Camera(-m_AsepctRatio * m_ZoomLevel, m_AsepctRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
        m_CamPos(0.0f),
        m_CamRotation(0.0f),
        m_CamTranslationSpeed(1.0f),
        m_CamRotationSpeed(180.0f)
    {
    }

    void OrthographicCameraController::OnUpdate(Timestep ts)
    {
        ZZX_PROFILE_FUNCTION();

        if (Input::IsKeyPressed(Key::A))
        {
            m_CamPos.x -= m_CamTranslationSpeed * ts;
        }
        else if (Input::IsKeyPressed(Key::D))
        {
            m_CamPos.x += m_CamTranslationSpeed * ts;
        }

        if (Input::IsKeyPressed(Key::S))
        {
            m_CamPos.y -= m_CamTranslationSpeed * ts;
        }
        else if (Input::IsKeyPressed(Key::W))
        {
            m_CamPos.y += m_CamTranslationSpeed * ts;
        }
        if (m_Rotation)
        {
            if (Input::IsKeyPressed(Key::Q))
            {
                m_CamRotation += m_CamRotationSpeed * ts;
            }

            else if (Input::IsKeyPressed(Key::E))
            {
                m_CamRotation -= m_CamRotationSpeed * ts;
            }
            m_Camera.SetRotation(m_CamRotation);
        }
        m_Camera.SetPosition(m_CamPos);      

        m_CamTranslationSpeed = m_ZoomLevel; // zooming in makes camera move slower
    }

    void OrthographicCameraController::OnEvent(Event& e)
    {
        ZZX_PROFILE_FUNCTION();

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(ZZX_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(ZZX_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
    }

    void OrthographicCameraController::OnResize(float w, float h)
    {
        m_AsepctRatio = w / h;
        m_Camera.SetProjection(-m_AsepctRatio * m_ZoomLevel, m_AsepctRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
    {
        ZZX_PROFILE_FUNCTION();

        m_ZoomLevel -= e.GetYOffset() * 0.25f;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        m_Camera.SetProjection(-m_AsepctRatio * m_ZoomLevel, m_AsepctRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }

    bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
    {
        ZZX_PROFILE_FUNCTION();

        OnResize((float)e.GetWidth(), (float)e.GetHeight());
        return false;
    }

}