#include <ZZX.h>
#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Platform/OpenGL/OpenGLShader.h"
#include "Sandbox2D.h"

class BadAssLayer : public ZZX::Layer
{
public:
    BadAssLayer()
        : Layer("BadAssLayer"),
        m_CameraController(1280.0f / 720.0f, false)
    {
        {
            m_TriangleVAO = ZZX::VertexArray::Create();
            float vertices[] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f, 0.5f, 0.0f
            };
            ZZX::Ref<ZZX::VertexBuffer> triangleVBO;
            triangleVBO = ZZX::VertexBuffer::Create(sizeof(vertices), vertices);
            triangleVBO->SetLayout({
                { ZZX::ShaderDataType::Float3, "a_Pos" }
            });
            m_TriangleVAO->AddVertexBuffer(triangleVBO);
            unsigned int indices[3] = { 0, 1, 2 };
            ZZX::Ref<ZZX::IndexBuffer> triangleEBO;
            triangleEBO = ZZX::IndexBuffer::Create(sizeof(indices) / sizeof(uint32_t), indices);
            m_TriangleVAO->SetIndexBuffer(triangleEBO);
        }


        {
            m_SquareVAO = ZZX::VertexArray::Create();
            float squareVertices[5 * 4] = {
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
                -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
            };
            ZZX::Ref<ZZX::VertexBuffer> squareVBO;
            squareVBO = ZZX::VertexBuffer::Create(sizeof(squareVertices), squareVertices);
            squareVBO->SetLayout({
                { ZZX::ShaderDataType::Float3, "a_Pos" },
                { ZZX::ShaderDataType::Float2, "a_TexCoord" }
            });
            m_SquareVAO->AddVertexBuffer(squareVBO);

            uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
            ZZX::Ref<ZZX::IndexBuffer> squareEBO;
            squareEBO = ZZX::IndexBuffer::Create(sizeof(squareIndices) / sizeof(uint32_t), squareIndices);
            m_SquareVAO->SetIndexBuffer(squareEBO);
        }


        std::string vertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Pos;

            uniform mat4 u_ViewProjMat;
            uniform mat4 u_ModelMat;
            out vec3 v_Pos;
          
            void main()
            {
                gl_Position = u_ViewProjMat * u_ModelMat * vec4(a_Pos, 1.0);
                v_Pos = a_Pos;
            }  
        )";

        std::string fragSrc = R"(
            #version 330 core
            out vec4 color;
            in vec3 v_Pos;
            void main()
            {
                color = vec4(v_Pos * 0.5 + 0.5, 1.0);
            }  
        )";

        m_Shader = ZZX::Shader::Create("VertexPosTriangle", vertexSrc, fragSrc);

        std::string flatColorShaderVS = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Pos;

            uniform mat4 u_ViewProjMat;
            uniform mat4 u_ModelMat;

            void main()
            {
                gl_Position = u_ViewProjMat * u_ModelMat * vec4(a_Pos, 1.0);
            }  
        )";

        std::string flatColorShaderFS = R"(
            #version 330 core
            out vec4 color;
            uniform vec3 u_Color;
            void main()
            {
                color = vec4(u_Color, 1.0);
            }  
        )";

        m_FlatShader = ZZX::Shader::Create("FlatColor", flatColorShaderVS, flatColorShaderFS);
        auto texShader = m_ShaderLib.Load("assets/shaders/Texture.glsl");

        m_Texture = ZZX::Texture2D::Create("assets/textures/Checkerboard.png");
        m_ChernoLogTexture = ZZX::Texture2D::Create("assets/textures/ChernoLogo.png");
        std::dynamic_pointer_cast<ZZX::OpenGLShader>(texShader)->Bind();
        std::dynamic_pointer_cast<ZZX::OpenGLShader>(texShader)->UploadInt("u_Texture", 0);
    }

    void OnUpdate(ZZX::Timestep timestep) override
    {       
        // Update
        m_CameraController.OnUpdate(timestep);

        // Render submission
        ZZX::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        ZZX::RenderCommand::Clear();

        ZZX::Renderer::BeginScene(m_CameraController.GetCamera());

        static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        std::dynamic_pointer_cast<ZZX::OpenGLShader>(m_FlatShader)->Bind();
        std::dynamic_pointer_cast<ZZX::OpenGLShader>(m_FlatShader)->UploadVec3("u_Color", m_SquareColor);

        for (int y = 0; y < 20; y++)
        {
            for (int x = 0; x < 20; x++)
            {
                glm::vec3 pos(x * 0.15f, y * 0.15f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                ZZX::Renderer::Submit(m_FlatShader, m_SquareVAO, transform);
            }
        }

        auto texShader = m_ShaderLib.Get("Texture");

        m_Texture->Bind(0);
        ZZX::Renderer::Submit(texShader, m_SquareVAO, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        m_ChernoLogTexture->Bind(0);
        ZZX::Renderer::Submit(texShader, m_SquareVAO, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
        //ZZX::Renderer::Submit(m_Shader, m_TriangleVAO);

        ZZX::Renderer::EndScene();
    }

    void OnImguiRender() override
    {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }

    void OnEvent(ZZX::Event& e) override
    {
        m_CameraController.OnEvent(e);
    }

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

class Game : public ZZX::Application
{
public:
    Game()
        : Application()
    {
        //PushLayer(new BadAssLayer());
        PushLayer(new Sandbox2D());
    }
    ~Game()
    {
    }
};

ZZX::Application* ZZX::CreateApplication()
{
    return new Game();
}

#include <ZZX/Core/EntryPoint.h>