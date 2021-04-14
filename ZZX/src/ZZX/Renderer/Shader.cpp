#include <glad/glad.h>
#include "zzxpch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace ZZX
{
    Ref<Shader> Shader::Create(const std::string& filePath)
    {
        // which api are we using? 
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            ZZX_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLShader>(filePath);
        }

        ZZX_CORE_ASSERT(false, "Unknown RenderAPI!");
        return nullptr;
    }

    Ref<Shader> Shader::Create(const std::string& name, std::string& vertexSource, const std::string& fragmentSource)
    {
        // which api are we using? 
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            ZZX_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLShader>(name, vertexSource, fragmentSource);
        }

        ZZX_CORE_ASSERT(false, "Unknown RenderAPI!");
        return nullptr;
    }

    void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
    {
        ZZX_CORE_ASSERT(!Exists(name), "Shader already exists!");
        m_Shaders[name] = shader;
    }

    void ShaderLibrary::Add(const Ref<Shader>& shader)
    {
        auto& name = shader->GetName();
        Add(name, shader);
    }

    Ref<Shader> ShaderLibrary::Load(const std::string& filePath)
    {
        auto shader = Shader::Create(filePath);
        Add(shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filePath)
    {
        auto shader = Shader::Create(filePath);
        Add(name, shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Get(const std::string& name)
    {
        ZZX_CORE_ASSERT(Exists(name), "Shader Not Found!");
        return m_Shaders[name];
    }

    bool ShaderLibrary::Exists(const std::string& name) const
    {
        return m_Shaders.find(name) != m_Shaders.end();
    }
}