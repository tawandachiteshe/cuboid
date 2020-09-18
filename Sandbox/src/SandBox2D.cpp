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

}

void SandBox2D::OnDetach()
{

}

void SandBox2D::OnUpdate(float dt)
{
    D3G::RenderCommand::SetClearColor({ 0.0f, 1.0f, 0.0f, 1.0f });
    m_CameraController.OnUpdate(dt);
    m_CameraController.SetZoomLevel(zoomLevel);
}

void SandBox2D::OnImGuiRender()
{
    ImGui::Begin("data");
    ImGui::Text("This is some useful text.");
    ImGui::End();
}

void SandBox2D::OnEvent(D3G::Event& event)
{
    m_CameraController.OnEvent(event);
}

SandBox2D::~SandBox2D()
{

}
