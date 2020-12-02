#pragma once
#include <string>
#include <Cuboid/Core/Cuboid.h>
#include "Panels/SceneHieracyPanel.h"


namespace Cuboid
{

    class CuboidEditor : public Cuboid::Layer
    {
    public:
        CuboidEditor(const std::string& name);

        void OnAttach() override;

        void OnDetach() override;

        void OnUpdate(float dt) override;

        void OnImGuiRender() override;

        void OnEvent(Cuboid::Event& event) override;

        bool OnWindowResized(WindowResizeEvent& e);

        ~CuboidEditor() override;

    private:

        struct Vertex
        {
            glm::vec3 pos;
            uint8_t color[4];
            glm::vec2 uv;
            int textureID;
        };

        Ref<VertexArray> m_Va;
        Ref<VertexBuffer> m_vb;
        Ref<IndexBuffer> m_ib;
        Ref<Shader> m_Shader;
        Ref<Shader> m_MeshShader;
        Ref<VertexBufferLayout> m_Layout;
        Ref<Texture2D> m_Texture;
        Ref<Texture2D> m_Texture2;
        Camera2DController m_CameraController;

        Ref<FrameBuffer> m_FrameBuffer;

        glm::vec2 m_vcViewPortSize = {0.0f, 0.0f};

        glm::vec2 m_vcWindowSize = { 1280.0f, 720.0f };

        bool m_bIsViewPortFocused, m_bIsViewPortHovered = false;

        Ref<Scene> m_scActiveScene;

        Entity squareEntity = {};
        Entity CameraEntity = {};
        Entity m_CubeEntity = {};

        SceneHieracyPanel m_SceneHieracyPanel;
    };

}
