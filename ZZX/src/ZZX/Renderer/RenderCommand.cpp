#include "zzxpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace ZE
{
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}