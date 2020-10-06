//
// Created by Jerry on 29/5/2020.
//
#include <glad/glad.h>
#include <imgui.h>
#include <SDL_timer.h>
#include <Cuboid/ImGui/ImGuiDock.h>
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
    CUBOID_CORE_INFO(std::forward<Args>(args)...);
}


SandBox2D::SandBox2D(const std::string &name) : Layer(name),
                                                m_CameraController(1280.0f/720.0f, true)
{
}



void SandBox2D::OnAttach()
{

    Cuboid::FrameBufferSpecification fbSpec;

    fbSpec.Width = 1280;
    fbSpec.Height = 720;
    
    m_FrameBuffer = Cuboid::FrameBuffer::Create(fbSpec);


#if 1
    m_Va = Cuboid::VertexArray::Create();

    m_Texture = Cuboid::Texture2D::Create(1, 1);

    m_Texture2 = Cuboid::Texture2D::Create(1, 1);

    

    uint32_t textureData[] = { 0xFF00FF00u, 0xFF0000FFu, 0xFF00FF00u, 0xFF0000FFu };

    uint32_t textureData2 = 0xFF0000FFu;

    m_Texture->SetData(textureData, sizeof(textureData));
    m_Texture2->SetData(&textureData2, sizeof(textureData));

    m_TextureArray = Cuboid::Texture2DArray::Create(2);

    m_TextureArray->AddTexture(m_Texture);
    m_TextureArray->AddTexture(m_Texture2);

    Vertex vertices[] = 
    {
        { {-1.5f, -1.5f, 0.0f }, { 255, 0, 0, 255 }, { 0.0f, 0.0f }, 1 },
        { { 1.5f, -1.5f, 0.0f  }, { 0, 0, 255, 255 }, { 0.0f, 1.0f }, 0 },
        { { 1.5f, 1.5f, 0.0f }, { 0, 255, 0, 255 },  { 1.0f, 0.0f }, 1 },
        { {-1.5f, 1.5f, 0.0f }, { 0 , 255, 255, 255 },  { 1.0f, 1.0f }, 0 }
    };

    m_vb = Cuboid::VertexBuffer::Create(sizeof(vertices));
    m_vb->SetData(vertices, sizeof(vertices));
    m_Shader = Cuboid::Shader::FromShaderSourceFiles("res/Shaders/FlatColorPixelShader.hlsl", "res/Shaders/FlatColorVertexShader.hlsl");
 
    m_vb->SetShader(m_Shader);
 
    m_TextureArray->Bind(0);

    m_vb->SetLayout({ { Cuboid::ShaderDataType::Float3, "a_Position" }, { Cuboid::ShaderDataType::Byte4, "a_Color" }, { Cuboid::ShaderDataType::Float2, "a_Texcoord" }, { Cuboid::ShaderDataType::Int, "a_textureidx" } });

    m_Va->AddVertexBuffer(m_vb);

    m_vb->Bind();
    uint32_t indices[] = { 0, 1, 2, 0, 2, 3 };
    m_ib = Cuboid::IndexBuffer::Create(indices, 6);

    m_Va->SetIndexBuffer(m_ib);

#endif

}

void SandBox2D::OnDetach()
{

}

void SandBox2D::OnUpdate(float dt)
{
    
   // Cuboid::RenderCommand::Clear();
   
    m_CameraController.OnUpdate(dt);
    m_CameraController.SetZoomLevel(zoomLevel);

    m_FrameBuffer->Bind();
    Cuboid::RenderCommand::SetViewport(0, 0, 1280, 720);
    
    const auto& scale = glm::scale(glm::mat4(1.0f), glm::vec3(xscale, yscale, 1.0f));

    Cuboid::Renderer::BeginScene(m_CameraController.GetCamera());

    Cuboid::Renderer::Submit(m_Va, m_Shader);

    Cuboid::Renderer::EndScene();

    Cuboid::Renderer2D::BeginScene(m_CameraController.GetCamera());

    Cuboid::Renderer2D::DrawQuad({ -1.5f, -1.5f }, { 2.0f, 2.0f }, {1.0f, 0.0f, 0.0f, 1.0f});
    
    Cuboid::Renderer2D::DrawQuad({ 0.5f, 0.5f }, { 2.0f, 2.0f }, { 0.0f, 1.0f, 0.0f, 1.0f });

    Cuboid::Renderer2D::DrawQuad({ 0.75f, 0.75f }, { 2.0f, 2.0f }, { 0.0f, 0.0f, 1.0f, 1.0f });

    Cuboid::Renderer2D::DrawQuad({ 1.0f, 0.0f }, { 2.0f, 2.0f });

    rot += dt * 45.f;

    Cuboid::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f }, { 4.0f, 4.0f }, rot, { 0.54f, 0.96f, 0.43f, 1.0f });

    Cuboid::Renderer2D::EndScene();

    m_FrameBuffer->UnBind();

    Cuboid::RenderCommand::SetClearColor({ 0.23f, 0.23f, 0.23f, 1.0f });
    Cuboid::RenderCommand::SetViewport(0, 0, 1280, 720);
    

    

}

void SandBox2D::OnImGuiRender()
{
    auto stats = Cuboid::Renderer2D::GetStats();

    ImGui::Begin("data");
    ImGui::Text("Draw calls %d", stats.DrawCalls);
    ImGui::Text("Number of indices %d", stats.GetTotalIndexCount());
    ImGui::Text("Number of vertices %d", stats.GetTotalVertexCount());
    ImGui::Text("Number of quads %d", stats.QuadCount);
    ImGui::End();

    ImGuiWindowFlags windowflags = 0;
    windowflags |= ImGuiWindowFlags_NoScrollWithMouse;
    windowflags |= ImGuiWindowFlags_NoScrollbar;

    ImGui::Begin("Editor", 0, windowflags);

    
   
    ImGui::Image(m_FrameBuffer->GetColorAttachmentRenderID(), { ImGui::GetWindowWidth(),  ImGui::GetWindowHeight() });

    ImGui::End();


    Cuboid::Renderer2D::ResetStats();

    
}

void SandBox2D::OnEvent(Cuboid::Event& event)
{
   //CUBOID_DEBUG(event.GetName());
   
    m_CameraController.OnEvent(event);
}

SandBox2D::~SandBox2D()
{

}
