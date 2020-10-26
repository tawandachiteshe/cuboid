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
        float PointSize;
        float Radius;
    };

    struct Renderer2DStorage
    {
        static PRIMITIVES PrimRenderState;

        static const uint32_t MaxPrimitives = 10000;
        static const uint32_t MaxQuadsVertices = MaxPrimitives * (uint32_t)PRIMITIVES::QUADS;
        static const uint32_t MaxQuadsIndices = MaxPrimitives * 6;

        static const uint32_t MaxTrianglesVertices = MaxPrimitives * (uint32_t)PRIMITIVES::TRIANGLES;
        static const uint32_t MaxTrianglesIndices = MaxPrimitives * 3;

        static const uint32_t MaxLinesVertices = MaxPrimitives * (uint32_t)PRIMITIVES::LINES;
        static const uint32_t MaxLinesIndices = MaxPrimitives * 2;

        static const uint32_t MaxPointsVertices = MaxPrimitives * (uint32_t)PRIMITIVES::POINTS;
        static const uint32_t MaxPointsIndices = MaxPrimitives * 1;

        static const int MaxTextureSlots = 8;


        uint32_t QuadIndexCount = 0;
        uint32_t TriangleIndexCount = 0;
        uint32_t LineIndexCount = 0;
        uint32_t PointIndexCount = 0;

        Ref<VertexArray> QuadVertexArray;
        Ref<VertexBuffer> QuadVertexBuffer;

        Ref<VertexArray> TriangleVertexArray;
        Ref<VertexBuffer> TriangleVertexBuffer;

        Ref<VertexArray> LineVertexArray;
        Ref<VertexBuffer> LineVertexBuffer;

        Ref<VertexArray> PointVertexArray;
        Ref<VertexBuffer> PointVertexBuffer;

        Ref<Shader> TextureShader;
        Ref<Texture2D> WhiteTexture;

        CuboidVertex *QuadVertexBufferBase = nullptr;
        CuboidVertex *QuadVertexBufferPtr = nullptr;

        CuboidVertex *TriangleVertexBufferBase = nullptr;
        CuboidVertex *TriangleVertexBufferPtr = nullptr;

        CuboidVertex *PointVertexBufferBase = nullptr;
        CuboidVertex *PointVertexBufferPtr = nullptr;


        CuboidVertex *LineVertexBufferBase = nullptr;
        CuboidVertex *LineVertexBufferPtr = nullptr;

        std::array<Ref<Texture2D>,  MaxTextureSlots> TextureSlots;
        uint32_t TextureSlotIndex = 1;

        glm::vec4 QuadVertexPositions[4];
        glm::vec4 TriangleVertexPositions[3];

     
        Renderer2D::Statistics Stats;
    };


    static Renderer2DStorage s_Storage;
    PRIMITIVES Renderer2DStorage::PrimRenderState = PRIMITIVES::NONE;


    void Renderer2D::InitTriangles()
    {
        Renderer2DStorage::PrimRenderState = PRIMITIVES::TRIANGLES;
        uint32_t *TriangleIndices = new uint32_t[Renderer2DStorage::MaxTrianglesIndices];

        uint32_t offset = 0;
        for (int i = 0; i < Renderer2DStorage::MaxTrianglesIndices; i += 3) {

            TriangleIndices[i + 0] = offset + 0;
            TriangleIndices[i + 1] = offset + 1;
            TriangleIndices[i + 2] = offset + 2;

            offset += 3;
        }

        s_Storage.TriangleVertexArray = VertexArray::Create();
        s_Storage.TriangleVertexArray->SetShader(s_Storage.TextureShader);
        s_Storage.TriangleVertexBuffer = VertexBuffer::Create(Renderer2DStorage::MaxTrianglesVertices * sizeof(CuboidVertex));
 
        s_Storage.TriangleVertexBuffer->SetShader(s_Storage.TextureShader);

        s_Storage.TriangleVertexBuffer->SetLayout({
                                                      {ShaderDataType::Float3, "a_Position"},
                                                      {ShaderDataType::Float4, "a_Color"},
                                                      {ShaderDataType::Float2, "a_TextureCoord"},
                                                      {ShaderDataType::Float1, "a_TextureIdx"},
                                                      {ShaderDataType::Float1, "a_TillingFactor"},
                                                      {ShaderDataType::Float1, "a_PointSize"},
                                                      {ShaderDataType::Float1, "a_Radius"}
                                              });

        s_Storage.TriangleVertexArray->AddVertexBuffer(s_Storage.TriangleVertexBuffer);
        s_Storage.TriangleVertexBufferBase = new CuboidVertex[Renderer2DStorage::MaxTrianglesVertices];

        Ref<IndexBuffer> idxBuffer = IndexBuffer::Create(TriangleIndices, Renderer2DStorage::MaxTrianglesIndices);
        s_Storage.TriangleVertexArray->SetIndexBuffer(idxBuffer);
        delete[] TriangleIndices;

        s_Storage.TriangleVertexPositions[0] = {-0.5f, -0.5f, 0.0f, 1.0f};
        s_Storage.TriangleVertexPositions[1] = {0.5f, -0.5f, 0.0f, 1.0f};
        s_Storage.TriangleVertexPositions[2] = {0.0f, 0.5f, 0.0f, 1.0f};

    }

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
                                                      {ShaderDataType::Float2, "a_TextureCoord"},
                                                      {ShaderDataType::Float1, "a_TextureIdx"},
                                                      {ShaderDataType::Float1, "a_TillingFactor"},
                                                      {ShaderDataType::Float1, "a_PointSize"},
                                                      {ShaderDataType::Float1, "a_Radius"}
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

    void Renderer2D::InitLines()
    {

        Renderer2DStorage::PrimRenderState = PRIMITIVES::LINES;
        uint32_t *LineIndices = new uint32_t[Renderer2DStorage::MaxLinesIndices];
        uint32_t offset = 0;
        for (int i = 0; i < Renderer2DStorage::MaxLinesIndices; i += 2) {

            LineIndices[i + 0] = offset + 0;
            LineIndices[i + 1] = offset + 1;
            offset += 2;

        }
        s_Storage.LineVertexArray = VertexArray::Create();
        s_Storage.LineVertexArray->SetShader(s_Storage.TextureShader);
        s_Storage.LineVertexBuffer = VertexBuffer::Create(Renderer2DStorage::MaxLinesVertices * sizeof(CuboidVertex));

        s_Storage.LineVertexBuffer->SetShader(s_Storage.TextureShader);
        s_Storage.LineVertexBuffer->SetLayout({
                                                          {ShaderDataType::Float3, "a_Position"},
                                                          {ShaderDataType::Float4, "a_Color"},
                                                          {ShaderDataType::Float2, "a_TextureCoord"},
                                                          {ShaderDataType::Float1, "a_TextureIdx"},
                                                          {ShaderDataType::Float1, "a_TillingFactor"},
                                                          {ShaderDataType::Float1, "a_PointSize"},
                                                          {ShaderDataType::Float1, "a_Radius"}
                                                  });
        s_Storage.LineVertexArray->AddVertexBuffer(s_Storage.LineVertexBuffer);
        s_Storage.LineVertexBufferBase = new CuboidVertex[Renderer2DStorage::MaxLinesVertices];
        Ref<IndexBuffer> idxBuffer = IndexBuffer::Create(LineIndices, Renderer2DStorage::MaxLinesIndices);
        s_Storage.LineVertexArray->SetIndexBuffer(idxBuffer);
        delete[] LineIndices;


    }

    void Renderer2D::InitPoints()
    {
        Renderer2DStorage::PrimRenderState = PRIMITIVES::POINTS;
        uint32_t *PointsIndices = new uint32_t[Renderer2DStorage::MaxPointsVertices];

        for (int i = 0; i < Renderer2DStorage::MaxPointsIndices; i += 1) {

            PointsIndices[i] = 0;

        }
        s_Storage.PointVertexArray = VertexArray::Create();
        s_Storage.PointVertexArray->SetShader(s_Storage.TextureShader);
        s_Storage.PointVertexBuffer = VertexBuffer::Create(Renderer2DStorage::MaxPointsVertices * sizeof(CuboidVertex));
      
        s_Storage.PointVertexBuffer->SetShader(s_Storage.TextureShader);
        s_Storage.PointVertexBuffer->SetLayout({
                                                          {ShaderDataType::Float3, "a_Position"},
                                                          {ShaderDataType::Float4, "a_Color"},
                                                          {ShaderDataType::Float2, "a_TextureCoord"},
                                                          {ShaderDataType::Float1, "a_TextureIdx"},
                                                          {ShaderDataType::Float1, "a_TillingFactor"},
                                                          {ShaderDataType::Float1, "a_PointSize"},
                                                          {ShaderDataType::Float1, "a_Radius"}
                                                  });
        s_Storage.PointVertexArray->AddVertexBuffer(s_Storage.PointVertexBuffer);
        s_Storage.PointVertexBufferBase = new CuboidVertex[Renderer2DStorage::MaxPointsVertices];
        Ref<IndexBuffer> idxBuffer = IndexBuffer::Create(PointsIndices, Renderer2DStorage::MaxPointsIndices);
        s_Storage.PointVertexArray->SetIndexBuffer(idxBuffer);
        delete[] PointsIndices;

    }

    //TODO: Run All this crap on a single vertexBuffer
    void Renderer2D::Init()
    {
        //glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, (int*)&Renderer2DStorage::MaxTextureSlots);

        std::string FragSrc, VertSrc = "";

        if (RendererAPI::GetAPI() == RendererAPI::API::Opengl)
        {

            FragSrc = "res/Shaders/Texture-frag.glsl";
            VertSrc = "res/Shaders/Texture-vert.glsl";

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
        InitTriangles();
        InitPoints();
        InitLines();

   

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
        delete[] s_Storage.TriangleVertexBufferBase;
        delete[] s_Storage.PointVertexBufferBase;
        delete[] s_Storage.LineVertexBufferBase;
        //TODO: DESTROY ALL THIS ON SHUTDOWN AND AND LINES BASEBUFFER
    }

    void Renderer2D::BeginScene(const Camera2D &camera)
    {
        s_Storage.TextureShader->Bind();
        s_Storage.TextureShader->SetMat4("u_ProjectionViewMatrix", camera.GetViewProjectionMatrix());

        s_Storage.QuadIndexCount = 0;
        s_Storage.QuadVertexBufferPtr = s_Storage.QuadVertexBufferBase;

        s_Storage.TriangleIndexCount = 0;
        s_Storage.TriangleVertexBufferPtr = s_Storage.TriangleVertexBufferBase;

        s_Storage.PointIndexCount = 0;
        s_Storage.PointVertexBufferPtr = s_Storage.PointVertexBufferBase;

        s_Storage.LineIndexCount = 0;
        s_Storage.LineVertexBufferPtr = s_Storage.LineVertexBufferBase;
        
        s_Storage.TextureSlotIndex = 1;
    }


    void Renderer2D::BeginScene(const Camera& camera, const glm::mat4& transform)
    {
        s_Storage.TextureShader->Bind();

        auto viewProj = camera.GetProjection() * glm::inverse(transform);

        s_Storage.TextureShader->SetMat4("u_ProjectionViewMatrix", viewProj);

        s_Storage.QuadIndexCount = 0;
        s_Storage.QuadVertexBufferPtr = s_Storage.QuadVertexBufferBase;

        s_Storage.TriangleIndexCount = 0;
        s_Storage.TriangleVertexBufferPtr = s_Storage.TriangleVertexBufferBase;

        s_Storage.PointIndexCount = 0;
        s_Storage.PointVertexBufferPtr = s_Storage.PointVertexBufferBase;

        s_Storage.LineIndexCount = 0;
        s_Storage.LineVertexBufferPtr = s_Storage.LineVertexBufferBase;

        s_Storage.TextureSlotIndex = 1;
    }

    void Renderer2D::EndScene()
    {

        uint32_t QuadDataSize = (uint8_t *) s_Storage.QuadVertexBufferPtr - (uint8_t *) s_Storage.QuadVertexBufferBase;
        s_Storage.QuadVertexBuffer->SetData(s_Storage.QuadVertexBufferBase, QuadDataSize);

        uint32_t TriangleDataSize = (uint8_t *) s_Storage.TriangleVertexBufferPtr - (uint8_t *) s_Storage.TriangleVertexBufferBase;
        s_Storage.TriangleVertexBuffer->SetData(s_Storage.TriangleVertexBufferBase, TriangleDataSize);

        uint32_t PointDataSize = (uint8_t *) s_Storage.PointVertexBufferPtr - (uint8_t *) s_Storage.PointVertexBufferBase;
        s_Storage.PointVertexBuffer->SetData(s_Storage.PointVertexBufferBase, PointDataSize);

        uint32_t LineDataSize = (uint8_t *) s_Storage.LineVertexBufferPtr - (uint8_t *) s_Storage.LineVertexBufferBase;
        s_Storage.LineVertexBuffer->SetData(s_Storage.LineVertexBufferBase, LineDataSize);
        
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

        if(s_Storage.TriangleIndexCount != 0)
            RenderCommand::DrawIndexed(s_Storage.TriangleVertexArray, s_Storage.TriangleIndexCount);

        if(s_Storage.PointIndexCount != 0)
            RenderCommand::DrawIndexed(s_Storage.PointVertexArray, s_Storage.PointIndexCount, 0x0000);

        if(s_Storage.PointIndexCount != 0)
            RenderCommand::DrawIndexed(s_Storage.LineVertexArray, s_Storage.LineIndexCount, 0x0001);

        s_Storage.Stats.DrawCalls++;
    }

    void Renderer2D::FlushAndReset()
    {
        EndScene();
        
        s_Storage.QuadIndexCount = 0;
        s_Storage.QuadVertexBufferPtr = s_Storage.QuadVertexBufferBase;

        s_Storage.TriangleIndexCount = 0;
        s_Storage.TriangleVertexBufferPtr = s_Storage.TriangleVertexBufferBase;

        s_Storage.PointIndexCount = 0;
        s_Storage.PointVertexBufferPtr = s_Storage.PointVertexBufferBase;

        s_Storage.LineIndexCount = 0;
        s_Storage.LineVertexBufferPtr = s_Storage.LineVertexBufferBase;
        
        s_Storage.TextureSlotIndex = 1.0f;
    }

    void Renderer2D::Fill(const glm::vec4 &color)
    {
    }

    void Renderer2D::DrawVertex(const glm::vec2 &position, float size, const glm::vec4 &color)
    {
        DrawVertex({ position.x, position.y, 1.0f}, size, color);
    }

    //TODO: Deprecate this function
    void Renderer2D::DrawVertex(const glm::vec3 &position, float size, const glm::vec4 &color)
    {
        Renderer2DStorage::PrimRenderState = PRIMITIVES::POINTS;
        constexpr size_t pointVertexCount = (size_t)PRIMITIVES::POINTS;
        const float textureIndex = 0.0f; // White Texture

        const float tilingFactor = 1.0f;
        const float radius = 0.0f;

        if (s_Storage.PointIndexCount >= Renderer2DStorage::MaxPointsIndices)
            FlushAndReset();

        for(int i = 0;  i < pointVertexCount; i++) {

            s_Storage.PointVertexBufferPtr->Positions = position;
            s_Storage.PointVertexBufferPtr->Color = color;
            s_Storage.PointVertexBufferPtr->TextureCoordinates = { 1.0f, 1.0f };
            s_Storage.PointVertexBufferPtr->TextureIdx = textureIndex;
            s_Storage.PointVertexBufferPtr->TillingFactor = tilingFactor;
            s_Storage.PointVertexBufferPtr->PointSize = size;
            s_Storage.PointVertexBufferPtr->Radius = radius;
            s_Storage.PointVertexBufferPtr++;
        }
        s_Storage.PointIndexCount += 1;
        s_Storage.Stats.QuadCount++;
    }

    void Renderer2D::DrawTriangle(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color)
    {
        DrawTriangle({position.x, position.y, 1.0f}, size, color);
    }
    void Renderer2D::DrawTriangle(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color)
    {
        Renderer2DStorage::PrimRenderState = PRIMITIVES::TRIANGLES;
        constexpr size_t triangleVertexCount = (size_t)PRIMITIVES::TRIANGLES;
        const float textureIndex = 0.0f; // White Texture
        constexpr glm::vec2 textureCoords[] = {{0.0f, 0.0f},
                                               {1.0f, 0.0f},
                                               {1.0f, 1.0f},
                                               };
        const float tilingFactor = 1.0f;
        const float pointsize = 1.0f;
        const float radius = 0.0f;

        if (s_Storage.TriangleIndexCount >= Renderer2DStorage::MaxTrianglesIndices)
            FlushAndReset();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
        for (size_t i = 0; i < triangleVertexCount; i++) {

            s_Storage.TriangleVertexBufferPtr->Positions = transform * s_Storage.TriangleVertexPositions[i];
            s_Storage.TriangleVertexBufferPtr->Color = color;
            s_Storage.TriangleVertexBufferPtr->TextureCoordinates = textureCoords[i];
            s_Storage.TriangleVertexBufferPtr->TextureIdx = textureIndex;
            s_Storage.TriangleVertexBufferPtr->TillingFactor = tilingFactor;
            s_Storage.TriangleVertexBufferPtr->PointSize = pointsize;
            s_Storage.TriangleVertexBufferPtr->Radius = radius;
            s_Storage.TriangleVertexBufferPtr++;

        }

        s_Storage.TriangleIndexCount += 3;
        s_Storage.Stats.QuadCount++;
    }
    void Renderer2D::DrawRotatedTriangle(const glm::vec2 &position, const glm::vec2 &size, float rotation,
                                         const glm::vec4 &color)
    {
        DrawRotatedTriangle({position.x, position.y, 1.0f}, size, rotation, color);
    }

    void Renderer2D::DrawRotatedTriangle(const glm::vec3 &position, const glm::vec2 &size, float rotation,
                                         const glm::vec4 &color)
    {
        Renderer2DStorage::PrimRenderState = PRIMITIVES::TRIANGLES;
        constexpr size_t triangleVertexCount = (size_t)PRIMITIVES::TRIANGLES;
        const float textureIndex = 0.0f; // White Texture
        constexpr glm::vec2 textureCoords[] = {{0.0f, 0.0f},
                                               {1.0f, 0.0f},
                                               {1.0f, 1.0f}};
        const float tilingFactor = 1.0f;
        const float pointsize = 1.0f;
        const float radius = 0.0f;

        if (s_Storage.TriangleIndexCount >= Renderer2DStorage::MaxTrianglesIndices)
            FlushAndReset();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
                              * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
                              * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

        for (size_t i = 0; i < triangleVertexCount; i++) {

            s_Storage.TriangleVertexBufferPtr->Positions = transform * s_Storage.TriangleVertexPositions[i];
            s_Storage.TriangleVertexBufferPtr->Color = color;
            s_Storage.TriangleVertexBufferPtr->TextureCoordinates = textureCoords[i];
            s_Storage.TriangleVertexBufferPtr->TextureIdx = textureIndex;
            s_Storage.TriangleVertexBufferPtr->TillingFactor = tilingFactor;
            s_Storage.TriangleVertexBufferPtr->PointSize = pointsize;
            s_Storage.TriangleVertexBufferPtr->Radius = radius;
            s_Storage.TriangleVertexBufferPtr++;

        }

        s_Storage.TriangleIndexCount += 3;
        s_Storage.Stats.QuadCount++;
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
            s_Storage.QuadVertexBufferPtr->PointSize = pointsize;
            s_Storage.QuadVertexBufferPtr->Radius = radius;
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
                s_Storage.QuadVertexBufferPtr->PointSize = pointsize;
                s_Storage.QuadVertexBufferPtr->Radius = radius;
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

    void Renderer2D::DrawCircle(const glm::vec2 &position, float radius, const glm::vec4 &color)
    {

        DrawCircle({ position.x, position.y, 1.0f }, radius, color);

    }

    void Renderer2D::DrawLine(const glm::vec2 &positionA, const glm::vec2 &positionB, float lineWidth,
                              const glm::vec4 &color)
    {
        DrawLine( { positionA.x, positionA.y, 1.0f }, { positionA.x, positionB.y, 1.0f }, lineWidth, color );
    }

    void Renderer2D::DrawLine(const glm::vec3 &positionA, const glm::vec3 &positionB, float lineWidth,
                              const glm::vec4 &color)
    {
        if(RendererAPI::GetAPI() == RendererAPI::API::Opengl)
            glLineWidth(lineWidth);

        const glm::vec3 LinePositions[2] = { positionA, positionB };

        Renderer2DStorage::PrimRenderState = PRIMITIVES::LINES;
        constexpr size_t lineVertexCount = (size_t)PRIMITIVES::LINES;
        const float textureIndex = 0.0f; // White Texture
        const float tilingFactor = 1.0f;
        const float radius = 0.0f;
        //const pointSize = 1.0f;
        if (s_Storage.LineIndexCount >= Renderer2DStorage::MaxLinesIndices)
            FlushAndReset();
        for(int i = 0;  i < lineVertexCount; i++) {

            s_Storage.LineVertexBufferPtr->Positions = LinePositions[i];
            s_Storage.LineVertexBufferPtr->Color = color;
            s_Storage.LineVertexBufferPtr->TextureCoordinates = { 1.0f, 1.0f };
            s_Storage.LineVertexBufferPtr->TextureIdx = textureIndex;
            s_Storage.LineVertexBufferPtr->TillingFactor = tilingFactor;
            s_Storage.LineVertexBufferPtr->PointSize = 1.0f;
            s_Storage.LineVertexBufferPtr->Radius = radius;
            s_Storage.LineVertexBufferPtr++;

        }
        s_Storage.LineIndexCount += 2;
        s_Storage.Stats.QuadCount++;

        if(RendererAPI::GetAPI() == RendererAPI::API::Opengl)
            glLineWidth(1.0f);
    }

    void Renderer2D::DrawCircle(const glm::vec3 &position, float radius, const glm::vec4 &color)
    {

        Renderer2DStorage::PrimRenderState = PRIMITIVES::QUADS;
        constexpr size_t quadVertexCount = (size_t)PRIMITIVES::QUADS;
        const float textureIndex = 0.0f; // White Texture
        constexpr glm::vec2 textureCoords[] = {{0.0f, 0.0f},
                                               {1.0f, 0.0f},
                                               {1.0f, 1.0f},
                                               {0.0f, 1.0f}};
        const float tilingFactor = 1.0f;
        const float pointsize = 1.0f;

        //TODO: Do this stuff ... plus im stupid yea the quad desides what the radius must be
        const float _radius = 1.0f;

        if (s_Storage.QuadIndexCount >= Renderer2DStorage::MaxQuadsIndices)
            FlushAndReset();
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
                              * glm::scale(glm::mat4(1.0f), {radius , radius, 1.0f});
        for (size_t i = 0; i < quadVertexCount; i++) {
            s_Storage.QuadVertexBufferPtr->Positions = transform * s_Storage.QuadVertexPositions[i];
            s_Storage.QuadVertexBufferPtr->Color = color;
            s_Storage.QuadVertexBufferPtr->TextureCoordinates = textureCoords[i];
            s_Storage.QuadVertexBufferPtr->TextureIdx = textureIndex;
            s_Storage.QuadVertexBufferPtr->TillingFactor = tilingFactor;
            s_Storage.QuadVertexBufferPtr->PointSize = pointsize;
            s_Storage.QuadVertexBufferPtr->Radius = _radius;
            s_Storage.QuadVertexBufferPtr++;
        }
        s_Storage.QuadIndexCount += 6;
        s_Storage.Stats.QuadCount++;

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
                s_Storage.QuadVertexBufferPtr->PointSize = pointsize;
                s_Storage.QuadVertexBufferPtr->Radius = radius;
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
            s_Storage.QuadVertexBufferPtr->PointSize = pointsize;
            s_Storage.QuadVertexBufferPtr->Radius = radius;
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