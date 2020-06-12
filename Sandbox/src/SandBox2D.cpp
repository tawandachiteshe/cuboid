//
// Created by Jerry on 29/5/2020.
//
#include <glad/glad.h>
#include <imgui.h>
#include <SDL_timer.h>
#include "SandBox2D.h"



static float zoomLevel = 1.0f;
static float fps = 0.0f;
static float rot = 0.0f;

template<typename ... Args>
static void LOGGER(Args&& ... args)
{
    D3G_CORE_INFO(std::forward<Args>(args)...);
}

struct Vector2
        {
            float x;
            float y;
        };

SandBox2D::SandBox2D(const std::string &name) : Layer(name), m_Camera2DController(1278.0f / 600.0f)
{
    lua.open_libraries(sol::lib::base);
    lua["print"] = LOGGER<std::string, std::string, std::string>;

    lua["vc"] = Vector2{};

    lua.new_usertype<Vector2>("Vector2",
                           "x", &Vector2::x,
                              "y",&Vector2::y
    );


    lua["draw_quad"] = [](const Vector2& pos,const Vector2& size){
        D3G::Renderer2D::DrawQuad({pos.x, pos.y}, {size.x, size.y}, {1.0f, 0.0f, 0.0f, 1.0f}); };



}

void SandBox2D::OnAttach()
{
    Tex1 = D3G::Texture2D::Create("res/images/logo.png");
}

void SandBox2D::OnDetach()
{

}

void SandBox2D::OnUpdate(float dt)
{
    fps =  dt;
    D3G::Renderer2D::ResetStats();
    rot += dt * 45;
    m_Camera2DController.OnUpdate(dt);


    D3G::RenderCommand::Clear();

    D3G::RenderCommand::SetClearColor({ 0.2f , 0.2f, 0.2, 1.0f});
    D3G::Renderer2D::BeginScene(m_Camera2DController.GetCamera());

    lua.script_file("res/scripts/game.lua");
    D3G::Renderer2D::DrawQuad({0.0f, 0.0f}, {5.0f, 5.0f});
    D3G::Renderer2D::GetShader()->SetFloat("u_time", (float)SDL_GetTicks() * 0.001);
    D3G::Renderer2D::EndScene();
}

void SandBox2D::OnImGuiRender()
{
    m_Camera2DController.SetZoomLevel(zoomLevel);
    auto renderStats = D3G::Renderer2D::GetStats();

    ImGui::Begin("Settings");

    ImGui::Text("D3G RENDERER2D STATS");
    ImGui::Text("D3G QUADS COUNT: %d", renderStats.QuadCount);
    ImGui::Text("D3G DRAW CALLS: %d", renderStats.DrawCalls);
    ImGui::Text("D3G DRAW Vertices: %d", renderStats.GetTotalVertexCount());
    ImGui::Text("D3G DRAW Indices: %d", renderStats.GetTotalIndexCount());
    ImGui::Text("D3G DRAW FPS: %f", 1.0f / fps);
    ImGui::SliderFloat("Camera Zoom Level", &zoomLevel, 0.25f, 6.0f);
    ImGui::SliderFloat("Rot control", &rot, 0.25f, 6.0f);
    ImGui::End();

}

void SandBox2D::OnEvent(SDL_Event *event)
{

    m_Camera2DController.OnEvent(event);
}

SandBox2D::~SandBox2D()
{

}
