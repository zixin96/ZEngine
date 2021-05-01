#pragma once
#include <glm/glm.hpp>

#include <unordered_map>

namespace ZE
{
    class Shader
    {
    public:
        virtual ~Shader() = default;
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual const std::string& GetName() const = 0;

        virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;
        virtual void SetVec4(const std::string& name, const glm::vec4& value) = 0;
        virtual void SetVec3(const std::string& name, const glm::vec3& value) = 0;
        virtual void SetInt(const std::string& name, int value) = 0;
        virtual void SetFloat(const std::string& name, float value) = 0;
        virtual void SetIntArray(const std::string& name, int* value, uint32_t count) = 0;

        static Ref<Shader> Create(const std::string& filePath);
        static Ref<Shader> Create(const std::string& name, std::string& vertexSource, const std::string& fragmentSource);
    };

    class ShaderLibrary
    {
    public:
        void Add(const std::string& name, const Ref<Shader>& shader);
        void Add(const Ref<Shader>& shader);
        Ref<Shader> Load(const std::string& filePath);
        Ref<Shader> Load(const std::string& name,  const std::string& filePath);
        Ref<Shader> Get(const std::string& name);
        bool Exists(const std::string& name) const;
    private:
        std::unordered_map<std::string, Ref<Shader>> m_Shaders;
    };
}
