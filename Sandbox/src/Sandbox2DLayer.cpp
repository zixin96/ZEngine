#include "Sandbox2DLayer.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "imgui/imgui.h"
#include <chrono>

Sandbox2DLayer::Sandbox2DLayer()
    : Layer("Sandbox2D"),
    m_CameraController(1280.0f / 720.0f, false)
{}

void Sandbox2DLayer::OnAttach()
{
    ZE_PROFILE_FUNCTION();

    m_CheckerboardTexture = ZE::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2DLayer::OnDetach()
{
    ZE_PROFILE_FUNCTION();
}

void Sandbox2DLayer::OnUpdate(ZE::Timestep timestep)
{ 
    ZE_PROFILE_FUNCTION();

    m_CameraController.OnUpdate(timestep);
    
    // Render
    // Reset stats here
    ZE::Renderer2D::ResetStats();
    {
        ZE_PROFILE_SCOPE("Renderer Prep");
        ZE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        ZE::RenderCommand::Clear();
    }

    {
        static float rotation = 0.0f;
        rotation += timestep * 20.0f;

        ZE_PROFILE_SCOPE("Renderer Draw");
        // Render submission
        ZE::Renderer2D::BeginScene(m_CameraController.GetCamera());
        ZE::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
        ZE::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
        ZE::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
        ZE::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
        ZE::Renderer2D::DrawRotatedQuad({ -2.0f,  0.0f,  0.0f }, { 1.0f, 1.0f }, glm::radians(rotation), m_CheckerboardTexture, 20.0f);
        ZE::Renderer2D::EndScene();

        ZE::Renderer2D::BeginScene(m_CameraController.GetCamera());
        for (float y = -5.0f; y < 5.0f; y += 0.5f)
        {
            for (float x = -5.0f; x < 5.0f; x += 0.5f)
            {
                glm::vec4 color = { 0.4f, (x + 5.0f) / 10.0f , (y + 5.0f) / 10.0f,  0.5f };
                ZE::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
            }
        }
        ZE::Renderer2D::EndScene();
    }
    
}

void Sandbox2DLayer::OnImguiRender()
{
    ZE_PROFILE_FUNCTION();

    ImGui::Begin("Settings");

    auto stats = ZE::Renderer2D::GetStats();
    ImGui::Text("Renderer2D Stats: ");
    ImGui::Text("Draw Calls: %d", stats.DrawCalls);
    ImGui::Text("Quads: %d", stats.QuadCount);
    ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
    ImGui::Text("Indices: %d", stats.GetTotalIndexCount());


    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}

void Sandbox2DLayer::OnEvent(ZE::Event& e)
{
    m_CameraController.OnEvent(e);
}
