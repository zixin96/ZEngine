#include "zzxpch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace ZZX
{

    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
        : m_ProjMat(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), 
        m_ViewMat(1.0f),
        m_ViewProjMat(m_ProjMat * m_ViewMat),
        m_Pos(0.0f),
        m_Rotation(0.0f)
    {}

    void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
    {
        ZE_PROFILE_FUNCTION();

        m_ProjMat = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        m_ViewProjMat = m_ProjMat * m_ViewMat;
    }

    void OrthographicCamera::SetPosition(const glm::vec3& position) {
        m_Pos = position; 
        RecomputeViewMatrix();
    }

    void OrthographicCamera::SetRotation(float rotation) {
        m_Rotation = rotation; 
        RecomputeViewMatrix();
    }

    void OrthographicCamera::RecomputeViewMatrix()
    {
        ZE_PROFILE_FUNCTION();

        glm::mat4 transform(1.0f);
        transform = glm::translate(transform, m_Pos);
        transform = glm::rotate(transform, glm::radians(m_Rotation), glm::vec3(0, 0, 1));
        m_ViewMat = glm::inverse(transform);
        m_ViewProjMat = m_ProjMat * m_ViewMat;
    }

}
