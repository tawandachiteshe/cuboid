//
// Created by Jerry on 29/5/2020.
//

#ifndef D3NGINE_RENDERER2D_H
#define D3NGINE_RENDERER2D_H
#include "Texture.h"
#include "D3NGINE/utils/IO/FileSystem.h"
#include "Camera2D.h"

namespace D3G
{

    class Renderer2D
    {
        public:
        static void Init();

        static void ShutDown();

        static void BeginScene(const Camera2D& camera);

        static void EndScene();

        static void Flush();

        static  void Fill(const glm::vec4& color);

        static void DrawLine(const glm::vec2& positionA, const glm::vec2& positionB ,float lineWidth = 1.0f, const glm::vec4& color = {1.0f, 1.0f, 1.0f, 1.0f});

        static void DrawLine(const glm::vec3& positionA, const glm::vec3& positionB ,float lineWidth = 1.0f, const glm::vec4& color = {1.0f, 1.0f, 1.0f, 1.0f});

        static void DrawCircle(const glm::vec2& position,float radius, const glm::vec4& color = {1.0f, 1.0f, 1.0f, 1.0f});

        static void DrawCircle(const glm::vec3& position,float radius, const glm::vec4& color = {1.0f, 1.0f, 1.0f, 1.0f});

        static void DrawVertex(const glm::vec2& position,float size, const glm::vec4& color = {1.0f, 1.0f, 1.0f, 1.0f});

        static void DrawVertex(const glm::vec3& position,float size, const glm::vec4& color = {1.0f, 1.0f, 1.0f, 1.0f});

        static void DrawTriangle(const glm::vec2& position,const glm::vec2& size, const glm::vec4& color = {1.0f, 1.0f, 1.0f, 1.0f});

        static void DrawTriangle(const glm::vec3& position,const glm::vec2& size, const glm::vec4& color = {1.0f, 1.0f, 1.0f, 1.0f});

        static void DrawRotatedTriangle(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);

        static void DrawRotatedTriangle(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);

        static void DrawQuad(const glm::vec2& position,const glm::vec2& size, const glm::vec4& color = {1.0f, 1.0f, 1.0f, 1.0f});

        static void DrawQuad(const glm::vec3& position,const glm::vec2& size, const glm::vec4& color = {1.0f, 1.0f, 1.0f, 1.0f});

        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

        static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);

        static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);

        static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

        static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

        struct Statistics
        {
            uint32_t DrawCalls = 0;
            uint32_t QuadCount = 0;
            uint32_t GetTotalVertexCount() { return QuadCount * 4; }
            uint32_t GetTotalIndexCount() { return QuadCount * 6; }
        };

        static void ResetStats();

        static Statistics GetStats();

        private:
        static void FlushAndReset();
        static void InitQuads();
        static void InitTriangles();
        static void InitLines();
        static void InitPoints();
        static void DrawDestroy();
    };
}

#endif //D3NGINE_RENDERER2D_H
