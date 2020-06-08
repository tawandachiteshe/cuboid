//
// Created by Jerry on 29/5/2020.
//

#ifndef D3NGINE_SANDBOX2D_H
#define D3NGINE_SANDBOX2D_H

#include <string>
#include <D3NGINE/Core/D3G.h>
#include <lua.hpp>
class SandBox2D : public D3G::Layer
{
    public:
    SandBox2D(const std::string &name);

    void OnAttach() override;

    void OnDetach() override;

    void OnUpdate(float dt) override;

    void OnImGuiRender() override;

    void OnEvent(SDL_Event *event) override;

    ~SandBox2D() override;

    private:
    D3G::Camera2DController m_Camera2DController;
    D3G::Ref<D3G::Texture2D> Tex1;
    lua_State *L = nullptr;
};

#endif //D3NGINE_SANDBOX2D_H
