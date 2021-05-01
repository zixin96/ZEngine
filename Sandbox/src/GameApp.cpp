#include <ZZX.h>
#include "Sandbox2DLayer.h"

class GameApp : public ZE::Application
{
public:
    GameApp()
        : Application()
    {
        //PushLayer(new BadAssLayer());
        PushLayer(new Sandbox2DLayer());
    }
    ~GameApp()
    {
    }
};

ZE::Application* ZE::CreateApplication()
{
    return new GameApp();
}

#include <ZZX/Core/EntryPoint.h> // This contains the main function