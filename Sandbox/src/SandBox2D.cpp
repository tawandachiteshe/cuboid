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
static float r, b, g;

static float getcolorfield (lua_State *L, const char *key) {
    float result; int isnum;
    lua_pushstring(L, key); /* push key */
    lua_gettable(L, -2); /* get background[key] */
    result = (lua_tonumberx(L, -1, &isnum));
    if (!isnum)
        luaL_error(L, "invalid component '%s' in color", key);
    lua_pop(L, 1); /* remove number */
    return result;
}

SandBox2D::SandBox2D(const std::string &name) : Layer(name), m_Camera2DController(1278.0f / 600.0f)
{

     L = luaL_newstate();
    luaL_openlibs(L);


    int a = luaL_loadfile(L, "res/scripts/RendererConf.lua");
    int b = lua_pcall(L, 0, 0, 0);
    int lua_globa = lua_getglobal(L, "a");
    if((a || b))
    {
        D3G_CORE_ERROR("lua Error {0}", lua_tostring(L, -1));
        lua_pop(L, 1);
    }

     lua_getglobal(L, "background");
    if (!lua_istable(L, 0))
        luaL_error(L, "'background' is not a table");
     r = getcolorfield(L, "red");
     g = getcolorfield(L, "green");
     b = getcolorfield(L, "blue");
    D3G_CORE_DEBUG("Colors from Lua ( {0}, {1}, {2} )", r, g, b);

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

    D3G::RenderCommand::SetClearColor({ r , g, b, 1.0f});
    D3G::Renderer2D::BeginScene(m_Camera2DController.GetCamera());

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
