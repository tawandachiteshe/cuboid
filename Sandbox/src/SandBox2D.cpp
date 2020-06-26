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

}

void SandBox2D::OnImGuiRender()
{
    //bool showDock = false;
    //D3G::ShowExampleAppDockSpace(&showDock);
   ImGui::Begin("Settings");

   ImGui::SliderFloat("Zoom level", &zoomLevel, 0.1, 10.0f);

    ImGui::End();

    ImGui::Begin("Utils");

    ImGui::End();

}

void SandBox2D::OnEvent(SDL_Event *event)
{
m_CameraController.OnEvent(event);
}

SandBox2D::~SandBox2D()
{

}
