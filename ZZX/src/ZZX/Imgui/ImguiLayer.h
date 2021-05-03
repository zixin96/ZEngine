#pragma once

#include "ZZX/Core/Layer.h"

#include "ZZX/Events/MouseEvent.h"
#include "ZZX/Events/KeyEvent.h"
#include "ZZX/Events/ApplicationEvent.h"

namespace ZE
{
    class ImguiLayer : public Layer
    {
    public:
        ImguiLayer();
        ~ImguiLayer() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnEvent(Event& e) override;

        // We use begin() and end() so that Layer::OnImGuiRender can be position in-between such that layers can control imgui rendering commands
        void Begin();
        void End();
        void SetBlockEvents(bool block) { m_BlockEvents = block; }
        void SetDarkThemeColors();
    private:
        bool m_BlockEvents;
        float m_Time;
    };
}


