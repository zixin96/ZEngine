#include <ZZX.h>
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

#include <ZZX/Core/EntryPoint.h> // This contains the main function>
