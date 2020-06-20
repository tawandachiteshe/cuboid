//
// Created by Jerry on 29/5/2020.
//
#include <glad/glad.h>
#include <imgui.h>
#include <SDL_timer.h>
#include <D3NGINE/ImGui/ImGuiDock.h>
#include "SandBox2D.h"

static float zoomLevel = 1.0f;
static float fps = 0.0f;
static float rot = 0.0f;

template<typename ... Args>
static void LOGGER(Args&& ... args)
{
    D3G_CORE_INFO(std::forward<Args>(args)...);
}


SandBox2D::SandBox2D(const std::string &name) : Layer(name),
                                                m_CameraController(1278.0f/600.0f)
{
}

void SandBox2D::OnAttach()
{

    m_Va = D3G::VertexArray::Create();

    const char* VertexShaderSrc = R"(

    cbuffer vertexBuffer : register(b0) {

        float4x4 projMat;
    };

    struct VertexShaderInput
    {
        float3 pos : Position;
        float4 col : Color;
    };

    struct PixelShaderOut
    {
        float4 pos : SV_POSITION;
        float4 col : Color;
    };

    PixelShaderOut main(VertexShaderInput input)
    {

      PixelShaderOut pixelDataout;
      pixelDataout.pos = mul(projMat, float4(input.pos.xyz, 1.0f));
      pixelDataout.col = input.col;

      return pixelDataout;
    }

    )";

    const char* PixelShaderSrc = R"(

    struct PixelShaderOut
    {
        float4 pos : SV_POSITION;
        float4 col : Color;
    };

    float4 main(PixelShaderOut pixelData) : SV_Target
    {
        return pixelData.col;
    }
    )";

    m_Shader = D3G::Shader::Create(PixelShaderSrc, VertexShaderSrc);


    float TriangleVertices[] = {-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                                 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
                                 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };

    m_vb = D3G::VertexBuffer::Create(TriangleVertices, sizeof(TriangleVertices));

    m_vb->SetLayout({ {D3G::ShaderDataType::Float3, "Position"},
                      {D3G::ShaderDataType::Float4, "Color"}});

    uint32_t indices[3] = { 0, 1, 2 };
    m_ib = D3G::IndexBuffer::Create(indices, 3);
    m_Va->SetShader(m_Shader);

    m_Va->AddVertexBuffer(m_vb);
    m_Va->SetIndexBuffer(m_ib);

}

void SandBox2D::OnDetach()
{

}

void SandBox2D::OnUpdate(float dt)
{
    //D3G_CORE_INFO("Up date {0}", dt);
    D3G::RenderCommand::Clear();
    D3G::RenderCommand::SetClearColor({1.0f, 0.23f, 0.23f, 1.0f});

    D3G::Renderer::BeginScene(m_CameraController.GetCamera());

    D3G::RenderCommand::DrawIndexed(m_Va);

    D3G::Renderer::EndScene();
}

void SandBox2D::OnImGuiRender()
{
    //bool showDock = false;
    //D3G::ShowExampleAppDockSpace(&showDock);
   ImGui::Begin("Settings");

    ImGui::End();

    ImGui::Begin("Utils");

    ImGui::End();

}

void SandBox2D::OnEvent(SDL_Event *event)
{

}

SandBox2D::~SandBox2D()
{

}
