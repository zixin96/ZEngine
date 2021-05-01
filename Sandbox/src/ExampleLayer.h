#pragma once

#include "ZZX.h"

class ExampleLayer : public ZZX::Layer
{
public:
    ExampleLayer();
 
    void OnUpdate(ZZX::Timestep timestep) override;

    void OnImguiRender() override;
   
    void OnEvent(ZZX::Event& e) override;
  
private:
    ZZX::ShaderLibrary m_ShaderLib;
    ZZX::Ref<ZZX::Shader>        m_FlatShader;
    ZZX::Ref<ZZX::VertexArray>   m_SquareVAO;

    ZZX::Ref<ZZX::Shader>        m_Shader;
    ZZX::Ref<ZZX::VertexArray>   m_TriangleVAO;

    ZZX::Ref<ZZX::Texture2D>     m_Texture, m_ChernoLogTexture;

    ZZX::OrthographicCameraController m_CameraController;

    glm::vec3 m_SquareColor{0.2f, 0.3f, 0.8f};
};

