#pragma once
#include "OrthographicCamera.h"
#include "Texture.h"
#include "ZZX/Renderer/Camera.h"

namespace ZZX
{
    class Renderer2D
    {
    public:
        static void Init();
        static void Shutdown();
        

        static void BeginScene(const OrthographicCamera& camera); // TODO: remove
        static void BeginScene(const Camera& camera, const glm::mat4& transform);
        static void EndScene();
        static void Flush();

        // primitives
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1, const glm::vec4& tintColor = glm::vec4(1.0f));
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1, const glm::vec4& tintColor = glm::vec4(1.0f));

        static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
        static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, float tilingFactor = 1, const glm::vec4& tintColor = glm::vec4(1.0f));

        static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotationRad, const glm::vec4& color);
        static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotationRad, const glm::vec4& color);
        static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotationRad, const Ref<Texture2D>& texture, float tilingFactor = 1, const glm::vec4& tintColor = glm::vec4(1.0f));
        static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotationRad, const Ref<Texture2D>& texture, float tilingFactor = 1, const glm::vec4& tintColor = glm::vec4(1.0f));
    
        static void DrawRotatedQuad(const glm::mat4& transform, float rotationRad, const glm::vec4& color);
        static void DrawRotatedQuad(const glm::mat4& transform, float rotationRad, const Ref<Texture2D>& texture, float tilingFactor = 1, const glm::vec4& tintColor = glm::vec4(1.0f));

        struct Statistics
        {
            uint32_t DrawCalls = 0;
            uint32_t QuadCount = 0;

            uint32_t GetTotalVertexCount() { return QuadCount * 4; }
            uint32_t GetTotalIndexCount() { return QuadCount * 6; }
        };

        static void ResetStats();
        static Statistics GetStats();
        
        static void FlushAndReset();
    };
}



