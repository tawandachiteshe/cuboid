#include <Cuboidpch.h>
#include "Renderer2D.h"
#include "VertexArray.h"
#include "RendererCommand.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <array>
#include "Texture2DArray.h"

namespace Cuboid
{
    enum class PRIMITIVES
    {
        QUADS = 4,
        TRIANGLES = 3,
        POINTS = 1,
        LINES = 2,
        NONE = 0
    };

    struct CuboidVertex
    {
        glm::vec3 Positions;
        glm::vec4 Color;
        glm::vec2 TextureCoordinates;
        float TextureIdx;
        float TillingFactor;

    };

    struct Renderer2DStorage
    {
        static PRIMITIVES PrimRenderState;

        static const uint32_t MaxPrimitives = 10000;
        static const uint32_t MaxQuadsVertices = MaxPrimitives * (uint32_t)PRIMITIVES::QUADS;
        static const uint32_t MaxQuadsIndices = MaxPrimitives * 6;


        static const int MaxTextureSlots = 8;


        uint32_t QuadIndexCount = 0;
        Ref<VertexArray> QuadVertexArray;
        Ref<VertexBuffer> QuadVertexBuffer;


        Ref<Shader> TextureShader;
        Ref<Texture2D> WhiteTexture;

        CuboidVertex *QuadVertexBufferBase = nullptr;
        CuboidVertex *QuadVertexBufferPtr = nullptr;

        std::array<Ref<Texture2D>,  MaxTextureSlots> TextureSlots;
        uint32_t TextureSlotIndex = 1;

        glm::vec4 QuadVertexPositions[4];
        glm::vec4 TriangleVertexPositions[3];

     
        Renderer2D::Statistics Stats;
    };


    static Renderer2DStorage s_Storage;
    PRIMITIVES Renderer2DStorage::PrimRenderState = PRIMITIVES::NONE;

    void Renderer2D::InitQuads()
    {
        Renderer2DStorage::PrimRenderState = PRIMITIVES::QUADS;
        uint32_t *QuadIndices = new uint32_t[Renderer2DStorage::MaxQuadsIndices];
        uint32_t offset = 0;

        for (int i = 0; i < Renderer2DStorage::MaxQuadsIndices; i += 6) {
            QuadIndices[i + 0] = offset + 0;
            QuadIndices[i + 1] = offset + 1;
            QuadIndices[i + 2] = offset + 2;

            QuadIndices[i + 3] = offset + 0;
            QuadIndices[i + 4] = offset + 2;
            QuadIndices[i + 5] = offset + 3;
            offset += 4;
        }
        s_Storage.QuadVertexArray = VertexArray::Create();
        

        s_Storage.QuadVertexBuffer = VertexBuffer::Create(Renderer2DStorage::MaxQuadsVertices * sizeof(CuboidVertex));

        s_Storage.QuadVertexBuffer->SetShader(s_Storage.TextureShader);
        s_Storage.QuadVertexBuffer->SetLayout({
                                                      {ShaderDataType::Float3, "a_Position"},
                                                      {ShaderDataType::Float4, "a_Color"},
                                                      {ShaderDataType::Float2, "a_TexCoord"},
                                                      {ShaderDataType::Float1, "a_TexIndex"},
                                                      {ShaderDataType::Float1, "a_TilingFactor"}
                                              });
        s_Storage.QuadVertexArray->AddVertexBuffer(s_Storage.QuadVertexBuffer);
        s_Storage.QuadVertexBufferBase = new CuboidVertex[Renderer2DStorage::MaxQuadsVertices];
        Ref<IndexBuffer> idxBuffer = IndexBuffer::Create(QuadIndices, Renderer2DStorage::MaxQuadsIndices);
        
        s_Storage.QuadVertexArray->SetIndexBuffer(idxBuffer);
        delete[] QuadIndices;
        s_Storage.QuadVertexPositions[0] = {-0.5f, -0.5f, 0.0f, 1.0f};
        s_Storage.QuadVertexPositions[1] = {0.5f, -0.5f, 0.0f, 1.0f};
        s_Storage.QuadVertexPositions[2] = {0.5f, 0.5f, 0.0f, 1.0f};
        s_Storage.QuadVertexPositions[3] = {-0.5f, 0.5f, 0.0f, 1.0f};

       
    }


    //TODO: Run All this crap on a single vertexBuffer
    void Renderer2D::Init()
    {
        //glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, (int*)&Renderer2DStorage::MaxTextureSlots);

        std::string FragSrc, VertSrc = "";

        if (RendererAPI::GetAPI() == RendererAPI::API::Opengl)
        {

            FragSrc = "res/Shaders/Texture3-frag.glsl";
            VertSrc = "res/Shaders/Texture3-vert.glsl";

        } else {

            FragSrc = "res/Shaders/TexturePixelShader.hlsl";
            VertSrc = "res/Shaders/TextureVertexShader.hlsl";
        }
        
        

        s_Storage.TextureShader = Shader::FromShaderSourceFiles(FragSrc, VertSrc);
        //Initialise primitives here or it wont work dick ... Reason we need vertexAttribs in a shader

        s_Storage.WhiteTexture = Texture2D::Create(1, 1);
        uint32_t whiteTextureData = 0xFFFFFFFF;
        s_Storage.WhiteTexture->SetData(&whiteTextureData, sizeof(whiteTextureData));

        InitQuads();


        int32_t samplers[Renderer2DStorage::MaxTextureSlots];
        for (uint32_t i = 0; i < Renderer2DStorage::MaxTextureSlots; i++)
            samplers[i] = i;

        for (uint32_t i = 0; i < Renderer2DStorage::MaxTextureSlots; i++)
            s_Storage.TextureSlots[i] = s_Storage.WhiteTexture;

        

        s_Storage.TextureShader->SetIntArray("u_Textures", samplers, Renderer2DStorage::MaxTextureSlots);
        s_Storage.TextureSlots[0] = s_Storage.WhiteTexture;

    }

    void Renderer2D::ShutDown()
    {
        DrawDestroy();
    }

    void Renderer2D::DrawDestroy()
    {
        delete[] s_Storage.QuadVertexBufferBase;
        //TODO: DESTROY ALL THIS ON SHUTDOWN AND AND LINES BASEBUFFER
    }

    void Renderer2D::BeginScene(const Camera2D &camera)
    {
        s_Storage.TextureShader->Bind();
        s_Storage.TextureShader->SetMat4("u_ProjectionViewMatrix", camera.GetViewProjectionMatrix());

        s_Storage.QuadIndexCount = 0;
        s_Storage.QuadVertexBufferPtr = s_Storage.QuadVertexBufferBase;

        s_Storage.TextureSlotIndex = 1;
    }


    void Renderer2D::BeginScene(const Camera& camera, const glm::mat4& transform)
    {
        s_Storage.TextureShader->Bind();

        auto viewProj = camera.GetProjection() * glm::inverse(transform);

        s_Storage.TextureShader->SetMat4("u_ProjectionView", viewProj);

        s_Storage.QuadIndexCount = 0;
        s_Storage.QuadVertexBufferPtr = s_Storage.QuadVertexBufferBase;

        s_Storage.TextureSlotIndex = 1;
    }

    void Renderer2D::EndScene()
    {

        uint32_t QuadDataSize = (uint8_t *) s_Storage.QuadVertexBufferPtr - (uint8_t *) s_Storage.QuadVertexBufferBase;
        s_Storage.QuadVertexBuffer->SetData(s_Storage.QuadVertexBufferBase, QuadDataSize);

        Flush();
    }


    void Renderer2D::Flush()
    {
        for (uint32_t i = 0; i < s_Storage.TextureSlotIndex; i++)
            s_Storage.TextureSlots[i]->Bind(i);

        if (s_Storage.QuadIndexCount != 0)
        {
            RenderCommand::DrawIndexed(s_Storage.QuadVertexArray, s_Storage.QuadIndexCount);

        }

        s_Storage.Stats.DrawCalls++;
    }

    void Renderer2D::FlushAndReset()
    {
        EndScene();
        
        s_Storage.QuadIndexCount = 0;
        s_Storage.QuadVertexBufferPtr = s_Storage.QuadVertexBufferBase;

        s_Storage.TextureSlotIndex = 1.0f;
    }


    void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color)
    {
        DrawQuad({position.x, position.y, 1.0f}, size, color);
    }


    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color)
    {


        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
        DrawQuad(transform, color);
  

    }

    void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture2D> &texture,
                              float tilingFactor, const glm::vec4 &tintColor)
    {
        DrawQuad({position.x, position.y, 0.0f}, size, texture, tilingFactor, tintColor);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture2D> &texture,
                              float tilingFactor, const glm::vec4 &tintColor)
    {

        Renderer2DStorage::PrimRenderState = PRIMITIVES::QUADS;
        constexpr size_t quadVertexCount = (size_t)PRIMITIVES::QUADS;

        constexpr glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f};
        constexpr glm::vec2 textureCoords[] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};

        if (s_Storage.QuadIndexCount >= Renderer2DStorage::MaxQuadsIndices)
            FlushAndReset();

        const float pointsize = 1.0f;
        const float radius = 0.0f;
        float textureIndex = 0.0f;

        for (uint32_t i = 1; i < s_Storage.TextureSlotIndex; i++)
        {
            if (*s_Storage.TextureSlots[i].get() == *texture.get()) {
                textureIndex = (float) i;
                break;
            }
        }

        if (textureIndex == 0.0f)
        {
            if (s_Storage.TextureSlotIndex >= Renderer2DStorage::MaxTextureSlots)
                FlushAndReset();
            textureIndex = (float) s_Storage.TextureSlotIndex;
            s_Storage.TextureSlots[s_Storage.TextureSlotIndex] = texture;
            s_Storage.TextureSlotIndex++;
        }

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
        * glm::scale(glm::mat4(1.0f), {
            size.x, size.y, 1.0f
        });

        for (size_t i = 0; i < quadVertexCount; i++)
        {
            s_Storage.QuadVertexBufferPtr->Positions = transform * s_Storage.QuadVertexPositions[i];
            s_Storage.QuadVertexBufferPtr->Color = color;
            s_Storage.QuadVertexBufferPtr->TextureCoordinates = textureCoords[i];
            s_Storage.QuadVertexBufferPtr->TextureIdx = 1.0f;//textureIndex;
            s_Storage.QuadVertexBufferPtr->TillingFactor = tilingFactor;
            s_Storage.QuadVertexBufferPtr++;
        }
        s_Storage.QuadIndexCount += 6;
        s_Storage.Stats.QuadCount++;

        }

        void Renderer2D::DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, float rotation,
                                         const glm::vec4 &color)
        {
            DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);

        }

        void Renderer2D::DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, float rotation,
                                         const glm::vec4 &color)
        {
            Renderer2DStorage::PrimRenderState = PRIMITIVES::QUADS;
            constexpr size_t quadVertexCount = (size_t)PRIMITIVES::QUADS;

            const float textureIndex = 0.0f; // White Texture
            const float radius = 0.0f;
            constexpr glm::vec2 textureCoords[] = {{0.0f, 0.0f},
                                                   {1.0f, 0.0f},
                                                   {1.0f, 1.0f},
                                                   {0.0f, 1.0f}};
            const float tilingFactor = 1.0f;
            const float pointsize = 1.0f;
            if (s_Storage.QuadIndexCount >= Renderer2DStorage::MaxQuadsIndices)
                FlushAndReset();

            glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
                                  * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
                                  * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

            for (size_t i = 0; i < quadVertexCount; i++) {
                s_Storage.QuadVertexBufferPtr->Positions = transform * s_Storage.QuadVertexPositions[i];
                s_Storage.QuadVertexBufferPtr->Color = color;
                s_Storage.QuadVertexBufferPtr->TextureCoordinates = textureCoords[i];
                s_Storage.QuadVertexBufferPtr->TextureIdx = textureIndex;
                s_Storage.QuadVertexBufferPtr->TillingFactor = tilingFactor;
                s_Storage.QuadVertexBufferPtr++;
            }

            s_Storage.QuadIndexCount += 6;
            s_Storage.Stats.QuadCount++;

        }


        void Renderer2D::DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, float rotation,
                                         const Ref<Texture2D> &texture, float tilingFactor, const glm::vec4 &tintColor)
        {
            DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);
        }

    void Renderer2D::ResetStats()
    {
        memset(&s_Storage.Stats, 0, sizeof(Statistics));
    }

    Renderer2D::Statistics Renderer2D::GetStats()
    {
        return s_Storage.Stats;
    }


    void Renderer2D::DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, float rotation,
                                         const Ref<Texture2D> &texture, float tilingFactor, const glm::vec4 &tintColor)
        {

      

            Renderer2DStorage::PrimRenderState = PRIMITIVES::QUADS;
            constexpr size_t quadVertexCount = (size_t)PRIMITIVES::QUADS;

            constexpr glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f};
            constexpr glm::vec2 textureCoords[] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};

            if (s_Storage.QuadIndexCount >= Renderer2DStorage::MaxQuadsIndices)
                FlushAndReset();

            float textureIndex = 0.0f;
            for (uint32_t i = 1; i < s_Storage.TextureSlotIndex; i++)
            {
                if (*s_Storage.TextureSlots[i].get() == *texture.get()) {
                    textureIndex = (float) i;
                    break;
                }
            }

            if (textureIndex == 0.0f)
            {
                if (s_Storage.TextureSlotIndex >= Renderer2DStorage::MaxTextureSlots)
                    FlushAndReset();
                textureIndex = (float) s_Storage.TextureSlotIndex;
                s_Storage.TextureSlots[s_Storage.TextureSlotIndex] = texture;
                s_Storage.TextureSlotIndex++;
            }

            glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
                                  * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
                                  * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

            const float pointsize = 1.0f;
            const float radius = 0.0f;

            for (size_t i = 0; i < quadVertexCount; i++)
            {
                s_Storage.QuadVertexBufferPtr->Positions = transform * s_Storage.QuadVertexPositions[i];
                s_Storage.QuadVertexBufferPtr->Color = color;
                s_Storage.QuadVertexBufferPtr->TextureCoordinates = textureCoords[i];
                s_Storage.QuadVertexBufferPtr->TextureIdx = textureIndex;
                s_Storage.QuadVertexBufferPtr->TillingFactor = tilingFactor;
                s_Storage.QuadVertexBufferPtr++;
            }
            s_Storage.QuadIndexCount += 6;
            s_Storage.Stats.QuadCount++;
        }

    void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
    {

        Renderer2DStorage::PrimRenderState = PRIMITIVES::QUADS;
        constexpr size_t quadVertexCount = (size_t)PRIMITIVES::QUADS;

        const float textureIndex = 0.0f; // White Texture
        constexpr glm::vec2 textureCoords[] = { {0.0f, 0.0f},
                                               {1.0f, 0.0f},
                                               {1.0f, 1.0f},
                                               {0.0f, 1.0f} };
        const float tilingFactor = 1.0f;
        const float pointsize = 1.0f;
        const float radius = 0.0f;

        if (s_Storage.QuadIndexCount >= Renderer2DStorage::MaxQuadsIndices)
            FlushAndReset();

        for (size_t i = 0; i < quadVertexCount; i++) {
            s_Storage.QuadVertexBufferPtr->Positions = transform * s_Storage.QuadVertexPositions[i];
            s_Storage.QuadVertexBufferPtr->Color = color;
            s_Storage.QuadVertexBufferPtr->TextureCoordinates = textureCoords[i];
            s_Storage.QuadVertexBufferPtr->TextureIdx = 1.0f;
            s_Storage.QuadVertexBufferPtr->TillingFactor = tilingFactor;
            s_Storage.QuadVertexBufferPtr++;
        }

        s_Storage.QuadIndexCount += 6;

        s_Storage.Stats.QuadCount++;

    }

    void Renderer2D::DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
    {

        //TODO implements textures
    }

    Ref<Shader> &Renderer2D::GetShader()
    {
        return s_Storage.TextureShader;
    }

}