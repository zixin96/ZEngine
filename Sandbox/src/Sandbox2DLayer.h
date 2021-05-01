#pragma once
#include "ZZX.h"

class Sandbox2DLayer : public ZE::Layer
{
public:
    Sandbox2DLayer();
    virtual ~Sandbox2DLayer() = default;
    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate(ZE::Timestep timestep) override;
    void OnImguiRender() override;
    void OnEvent(ZE::Event& e) override;
private:
    ZE::OrthographicCameraController   m_CameraController;

    // Temp
    ZE::Ref<ZE::VertexArray>          m_SquareVAO;
    ZE::Ref<ZE::Shader>               m_FlatShader;
    glm::vec4                           m_SquareColor{ 0.2f, 0.3f, 0.8f, 1.0f };
    ZE::Ref<ZE::Texture2D>            m_CheckerboardTexture;
};

