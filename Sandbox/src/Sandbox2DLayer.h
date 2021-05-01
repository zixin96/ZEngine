#pragma once
#include "ZZX.h"

class Sandbox2DLayer : public ZZX::Layer
{
public:
    Sandbox2DLayer();
    virtual ~Sandbox2DLayer() = default;
    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate(ZZX::Timestep timestep) override;
    void OnImguiRender() override;
    void OnEvent(ZZX::Event& e) override;
private:
    ZZX::OrthographicCameraController   m_CameraController;

    // Temp
    ZZX::Ref<ZZX::VertexArray>          m_SquareVAO;
    ZZX::Ref<ZZX::Shader>               m_FlatShader;
    glm::vec4                           m_SquareColor{ 0.2f, 0.3f, 0.8f, 1.0f };
    ZZX::Ref<ZZX::Texture2D>            m_CheckerboardTexture;
};

