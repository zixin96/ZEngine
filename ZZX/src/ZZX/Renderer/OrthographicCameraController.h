#pragma once

#include "ZZX/Renderer/OrthographicCamera.h"
#include "ZZX/Core/Timestep.h"
#include "ZZX/Events/ApplicationEvent.h"
#include "ZZX/Events/MouseEvent.h"

namespace ZZX
{
    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);

        void OnUpdate(Timestep ts);
        void OnEvent(Event& e);
        OrthographicCamera& GetCamera() { return m_Camera; }
        const OrthographicCamera& GetCamera() const { return m_Camera; }
        void OnResize(float w, float h);
    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);
    private:
        float m_AsepctRatio;
        float m_ZoomLevel;
        bool m_Rotation;
        OrthographicCamera m_Camera;
        glm::vec3 m_CamPos;
        float m_CamRotation;
        float m_CamTranslationSpeed;
        float m_CamRotationSpeed;
    };
}



