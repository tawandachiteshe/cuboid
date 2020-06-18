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


SandBox2D::SandBox2D(const std::string &name) : Layer(name)
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
    //D3G_CORE_INFO("Up date {0}", dt);
    D3G::RenderCommand::Clear();
    D3G::RenderCommand::SetClearColor({1.0f, 0.23f, 0.23f, 1.0f});

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
