#include "zzxpch.h"
#include "Framebuffer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"
#include "Renderer.h"

namespace ZE
{
    
    Ref<ZE::Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
    {
        // which api are we using? 
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            ZE_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLFramebuffer>(spec);
        }

        ZE_CORE_ASSERT(false, "Unknown RenderAPI!");
        return nullptr;
    }

}