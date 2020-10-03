//
// Created by Jerry on 29/5/2020.
//

#ifndef D3NGINE_SANDBOX2D_H
#define D3NGINE_SANDBOX2D_H

#include <string>
#include <D3NGINE/Core/D3G.h>
#include <sol/sol.hpp>
class SandBox2D : public D3G::Layer
{
    public:
    SandBox2D(const std::string &name);

    void OnAttach() override;

    void OnDetach() override;

    void OnUpdate(float dt) override;

    void OnImGuiRender() override;

    void OnEvent(D3G::Event& event) override;

    ~SandBox2D() override;

    private:

        struct Vertex
        {
            glm::vec3 pos;
            glm::vec4 color;
            glm::vec2 uv;
            int textureID;
        };

    D3G::Ref<D3G::VertexArray> m_Va;
    D3G::Ref<D3G::VertexBuffer> m_vb;
    D3G::Ref<D3G::IndexBuffer> m_ib;
    D3G::Ref<D3G::Shader> m_Shader;
    D3G::Ref<D3G::VertexBufferLayout> m_Layout;
    D3G::Ref<D3G::Texture2D> m_Texture;
    D3G::Ref<D3G::Texture2D> m_Texture2;
    D3G::Camera2DController m_CameraController;
    D3G::Ref<D3G::Texture2DArray> m_TextureArray;
};

#endif //D3NGINE_SANDBOX2D_H
