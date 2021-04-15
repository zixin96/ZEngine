#pragma once
#include "ZZX/Core/Core.h"
#include "ZZX/Scene/Scene.h"
#include "ZZX/Scene/Entity.h"

namespace ZZX
{
    class SceneHierarchyPanel
    {
    public:
        SceneHierarchyPanel() = default;
        SceneHierarchyPanel(const Ref<Scene>& scene);
        void SetContext(const Ref<Scene>& scene);
        void OnImGuiRender();
		Entity GetSelectedEntity() const { return m_SelectionContext; }
    private:
        void DrawEntityNode(Entity entity);
        void DrawComponents(Entity entity);
    private:
        Ref<Scene> m_Context;
        Entity m_SelectionContext;
    };
}

