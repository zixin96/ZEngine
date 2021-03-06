#pragma once
#include "ZZX.h"
#include "Panels/SceneHierarchyPanel.h"
#include "ZZX/Renderer/EditorCamera.h"

namespace ZZX
{
    class EditorLayer : public Layer
    {
    public:
        EditorLayer();
        virtual ~EditorLayer() = default;
        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate(Timestep timestep) override;
        void OnImguiRender() override;
        void OnEvent(Event& e) override;
	private:
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		void NewScene();
		void OpenScene();
		void SaveSceneAs();
    private:
        OrthographicCameraController   m_CameraController;

        // Temp
        Ref<VertexArray>          m_SquareVAO;
        Ref<Shader>               m_FlatShader;
        Ref<Framebuffer>          m_Framebuffer;

        Ref<Scene>                m_ActiveScene;
        Entity                    m_SquareEntity;
        Entity                    m_CameraA;
        Entity                    m_CameraB;

        bool m_PrimaryCam = true;

        Ref<Texture2D>            m_CheckerboardTexture;

        bool m_ViewportFocused = false;
        bool m_ViewportHovered = false;

        glm::vec2                 m_ViewportSize{ 0.0f, 0.0f };
        SceneHierarchyPanel m_SceneHierarchyPanel;

		int m_GizmoType = -1;
		EditorCamera m_EditorCamera;

		glm::vec2 m_ViewportBounds[2];
		Entity m_HoveredEntity;
    };
}


