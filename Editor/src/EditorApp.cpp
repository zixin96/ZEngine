#include <ZZX.h>
#include <ZZX/Core/EntryPoint.h>
#include "EditorLayer.h"

namespace ZZX
{
    class Editor : public Application
    {
    public:
        Editor()
            : Application("Editor")
        {
            PushLayer(new EditorLayer());
        }
        ~Editor()
        {
        }
    };

    Application* CreateApplication()
    {
        return new Editor();
    }

}

