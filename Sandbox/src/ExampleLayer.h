#pragma once

#include "ZZX.h"

class ExampleLayer : public ZE::Layer
{
public:
    ExampleLayer();
 
    void OnUpdate(ZE::Timestep timestep) override;

    void OnImguiRender() override;
   
    void OnEvent(ZE::Event& e) override;
  
private:
    ZE::ShaderLibrary m_ShaderLib;
    ZE::Ref<ZE::Shader>        m_FlatShader;
    ZE::Ref<ZE::VertexArray>   m_SquareVAO;

    ZE::Ref<ZE::Shader>        m_Shader;
    ZE::Ref<ZE::VertexArray>   m_TriangleVAO;

    ZE::Ref<ZE::Texture2D>     m_Texture, m_ChernoLogTexture;

    ZE::OrthographicCameraController m_CameraController;

    glm::vec3 m_SquareColor{0.2f, 0.3f, 0.8f};
};

