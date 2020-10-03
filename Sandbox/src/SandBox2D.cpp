//
// Created by Jerry on 29/5/2020.
//
#include <glad/glad.h>
#include <imgui.h>
#include <SDL_timer.h>
#include <D3NGINE/ImGui/ImGuiDock.h>
#include "SandBox2D.h"
#include <DirectXMath.h>
#include <glm/gtc/matrix_transform.hpp>

static float zoomLevel = 1.0f;
static float fps = 0.0f;
static float rot = 0.0f;

static float xscale, yscale = 1.0f;

template<typename ... Args>
static void LOGGER(Args&& ... args)
{
    D3G_CORE_INFO(std::forward<Args>(args)...);
}


SandBox2D::SandBox2D(const std::string &name) : Layer(name),
                                                m_CameraController(1280.0f/720.0f, true)
{
}



void SandBox2D::OnAttach()
{
#if 1
    m_Va = D3G::VertexArray::Create();

    m_Texture = D3G::Texture2D::Create(1, 1);

    m_Texture2 = D3G::Texture2D::Create(1, 1);

    

    uint32_t textureData[] = { 0xFF00FF00u, 0xFF0000FFu, 0xFF00FF00u, 0xFF0000FFu };

    uint32_t textureData2 = 0xFF0000FFu;

    m_Texture->SetData(textureData, sizeof(textureData));
    m_Texture2->SetData(&textureData2, sizeof(textureData));

    m_TextureArray = D3G::Texture2DArray::Create(2);

    m_TextureArray->AddTexture(m_Texture);
    m_TextureArray->AddTexture(m_Texture2);

    Vertex vertices[] = 
    {
        { {-0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }, 1 },
        { { 0.5f, -0.5f, 0.0f  }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 0.0f, 1.0f }, 0 },
        { { 0.5f, 0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f },  { 1.0f, 0.0f }, 1 },
        { {-0.5f, 0.5f, 0.0f }, { 0.0f, 1.0f, 1.0f, 1.0f },  { 1.0f, 1.0f }, 0 }
    };

    m_vb = D3G::VertexBuffer::Create(sizeof(vertices));
    m_vb->SetData(vertices, sizeof(vertices));
    m_Shader = D3G::Shader::FromShaderSourceFiles("res/Shaders/FlatColorPixelShader.hlsl", "res/Shaders/FlatColorVertexShader.hlsl");
 
    m_vb->SetShader(m_Shader);
 
    //m_TextureArray->Bind(0);

    m_vb->SetLayout({ { D3G::ShaderDataType::Float3, "a_Position" }, { D3G::ShaderDataType::Float4, "a_Color" }, { D3G::ShaderDataType::Float2, "a_Texcoord" }, { D3G::ShaderDataType::Int, "a_textureidx" } });

    m_Va->AddVertexBuffer(m_vb);

    //m_vb->Bind();
    uint32_t indices[] = { 0, 1, 2, 0, 2, 3 };
    m_ib = D3G::IndexBuffer::Create(indices, 6);

    m_Va->SetIndexBuffer(m_ib);

#endif

}

void SandBox2D::OnDetach()
{

}

void SandBox2D::OnUpdate(float dt)
{
    D3G::RenderCommand::SetViewport(0, 0, 1280, 720);
   // D3G::RenderCommand::Clear();
    D3G::RenderCommand::SetClearColor({ 0.23f, 0.23f, 0.23f, 1.0f });
    m_CameraController.OnUpdate(dt);
    m_CameraController.SetZoomLevel(zoomLevel);

    //D3G_DEBUG("{0}, {1}", D3G::Input::GetMousePosition().first, D3G::Input::GetMousePosition().second);


    
    const auto& scale = glm::scale(glm::mat4(1.0f), glm::vec3(xscale, yscale, 1.0f));

    D3G::Renderer2D::BeginScene(m_CameraController.GetCamera());
   
    
   //D3G::Renderer::Submit(m_Va, m_Shader);
   
    D3G::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 2.0f, 2.0f }, {1.0f, 0.0f, 0.0f, 1.0f});
    
    D3G::Renderer2D::DrawQuad({ 0.5f, 0.5f }, { 2.0f, 2.0f }, { 0.0f, 1.0f, 0.0f, 1.0f });

    D3G::Renderer2D::DrawQuad({ 0.75f, 0.75f }, { 2.0f, 2.0f }, { 0.0f, 0.0f, 1.0f, 1.0f });

    D3G::Renderer2D::DrawQuad({ 1.0f, 0.0f }, { 2.0f, 2.0f }, m_Texture);

    D3G::Renderer2D::EndScene();
    

}

void SandBox2D::OnImGuiRender()
{
    auto stats = D3G::Renderer2D::GetStats();

    ImGui::Begin("data");
    ImGui::Text("Draw calls %d", stats.DrawCalls);
    ImGui::Text("Number of indices %d", stats.GetTotalIndexCount());
    ImGui::Text("Number of vertices %d", stats.GetTotalVertexCount());
    ImGui::Text("Number of quads %d", stats.QuadCount);

    ImGui::Image(m_Texture2->GetTextureID(), { 256.0f, 256.0f });

    D3G::Renderer2D::ResetStats();

    ImGui::DragFloat("Scale x", &xscale, 0.1f);
    ImGui::DragFloat("Scale y", &yscale, 0.1f);

    ImGui::End();
}

void SandBox2D::OnEvent(D3G::Event& event)
{
   //D3G_DEBUG(event.GetName());
   
    m_CameraController.OnEvent(event);
}

SandBox2D::~SandBox2D()
{

}
