#pragma once

#include <glm/glm.hpp>

namespace ZE
{
    class OrthographicCamera
    {
    public:
        OrthographicCamera(float left, float right, float bottom, float top); // default near = -1.0, far = 1.0
        void SetProjection(float left, float right, float bottom, float top);

        const glm::vec3& GetPosition() const { return m_Pos; }
        void SetPosition(const glm::vec3& position);

        float GetRotation() const { return m_Rotation; }
        void SetRotation(float rotation);

        const glm::mat4& GetProjectionMatrix() const { return m_ProjMat; }
        const glm::mat4& GetViewMatrix() const { return m_ViewMat; }
        const glm::mat4& GetViewProjMatrix() const { return m_ViewProjMat; }
    private:
        void RecomputeViewMatrix();
    private:
        glm::mat4 m_ProjMat;
        glm::mat4 m_ViewMat;
        glm::mat4 m_ViewProjMat;

        glm::vec3 m_Pos;
        float m_Rotation;
    };
}

