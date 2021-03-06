#include "zzxpch.h"
#include "Framebuffer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"
#include "Renderer.h"

namespace ZZX
{
    
    Ref<ZZX::Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
    {
        // which api are we using? 
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            ZZX_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLFramebuffer>(spec);
        }

        ZZX_CORE_ASSERT(false, "Unknown RenderAPI!");
        return nullptr;
    }

}