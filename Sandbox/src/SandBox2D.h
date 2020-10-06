//
// Created by Jerry on 29/5/2020.
//

#ifndef CUBOID_SANDBOX2D_H
#define CUBOID_SANDBOX2D_H

#include <string>
#include <Cuboid/Core/Cuboid.h>
#include <sol/sol.hpp>
class SandBox2D : public Cuboid::Layer
{
    public:
    SandBox2D(const std::string &name);

    void OnAttach() override;

    void OnDetach() override;

    void OnUpdate(float dt) override;

    void OnImGuiRender() override;

    void OnEvent(Cuboid::Event& event) override;

    ~SandBox2D() override;

    private:

        struct Vertex
        {
            glm::vec3 pos;
            uint8_t color[4];
            glm::vec2 uv;
            int textureID;
        };

    Cuboid::Ref<Cuboid::VertexArray> m_Va;
    Cuboid::Ref<Cuboid::VertexBuffer> m_vb;
    Cuboid::Ref<Cuboid::IndexBuffer> m_ib;
    Cuboid::Ref<Cuboid::Shader> m_Shader;
    Cuboid::Ref<Cuboid::VertexBufferLayout> m_Layout;
    Cuboid::Ref<Cuboid::Texture2D> m_Texture;
    Cuboid::Ref<Cuboid::Texture2D> m_Texture2;
    Cuboid::Camera2DController m_CameraController;
    Cuboid::Ref<Cuboid::Texture2DArray> m_TextureArray;

    Cuboid::Ref<Cuboid::FrameBuffer> m_FrameBuffer;
};

#endif //CUBOID_SANDBOX2D_H
