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
                                                m_CameraController(1280.0f/720.0f)
{
}



void SandBox2D::OnAttach()
{
    m_Va = D3G::VertexArray::Create();

    Vertex vertices[] = 
    {
        { { -0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
        { { -0.5f,  0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
        { { 0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
         { { 0.5f, 0.5f, 0.0f }, { 0.0f, 1.0f, 1.0f, 1.0f } }
    };

    m_vb = D3G::VertexBuffer::Create(vertices, sizeof(vertices));
    m_Shader = D3G::Shader::FromShaderSourceFiles("res/Shaders/FlatColorPixelShader.hlsl", "res/Shaders/FlatColorVertexShader.hlsl");
    m_vb->Bind();
    m_vb->SetShader(m_Shader);
 

    m_vb->SetLayout( { { D3G::ShaderDataType::Float3, "POSITION" }, { D3G::ShaderDataType::Float4, "COLOR" } } );

    m_Va->AddVertexBuffer(m_vb);

    m_vb->Bind();
    uint32_t indices[] = { 0, 1, 2, 2, 1, 3 };
    m_ib = D3G::IndexBuffer::Create(indices, 6);
    m_ib->Bind();

    m_Va->SetIndexBuffer(m_ib);

    m_Va->Bind();

}

void SandBox2D::OnDetach()
{

}

void SandBox2D::OnUpdate(float dt)
{
    D3G::RenderCommand::SetViewport(0, 0, 1280, 720);
    D3G::RenderCommand::SetClearColor({ 0.23f, 0.23f, 0.23f, 1.0f });
    m_CameraController.OnUpdate(dt);
    m_CameraController.SetZoomLevel(zoomLevel);

    //D3G_DEBUG("{0}, {1}", D3G::Input::GetMousePosition().first, D3G::Input::GetMousePosition().second);

    

    m_vb->Bind();

    const auto& scale = glm::scale(glm::mat4(1.0f), glm::vec3(xscale, yscale, 1.0f));

   
    m_Shader->Bind();
    m_Shader->SetMat4("dads", m_CameraController.GetCamera().GetViewProjectionMatrix());


    m_ib->Bind();
    
   
    D3G::RenderCommand::DrawIndexed(m_Va);
}

void SandBox2D::OnImGuiRender()
{
    ImGui::Begin("data");
    ImGui::Text("This is some useful text.");

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
