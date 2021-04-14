#pragma once

#include "ZZX/Core/Core.h"
#include "ZZX/Events/Event.h"
#include "ZZX/Core/Timestep.h"

namespace ZZX
{
    class Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(Timestep timestep) {}
        virtual void OnImguiRender() {}
        virtual void OnEvent(Event& event) {}

        inline const std::string& GetName() const { return m_DebugName; }
    protected:
        std::string m_DebugName;
    };
}


