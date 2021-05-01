#pragma once

// Layer renders graphics and receives events

#include "ZZX/Core/Base.h"
#include "ZZX/Events/Event.h"
#include "ZZX/Core/Timestep.h"

namespace ZE
{
    class Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(Timestep timestep) {}
        virtual void OnImguiRender() {}
        virtual void OnEvent(Event& event) {}

        const std::string& GetName() const { return m_DebugName; }
    protected:
        std::string m_DebugName;
    };
}


