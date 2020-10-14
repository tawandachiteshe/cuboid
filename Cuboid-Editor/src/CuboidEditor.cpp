#include "CuboidEditor.h"
#include "imgui.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

static float zoomLevel = 1.0f;
static float fps = 0.0f;
static float rot = 0.0f;

static float xscale, yscale = 1.0f;

static glm::vec4 SquareColor = { 0.54f, 0.96f, 0.43f, 1.0f };


namespace Cuboid
{

    CuboidEditor::CuboidEditor(const std::string& name) : Layer(name),
        m_CameraController(1280.0f / 720.0f, true)
    {
    }



    void CuboidEditor::OnAttach()
    {

        Cuboid::FrameBufferSpecification fbSpec;

        fbSpec.Width = 1280;
        fbSpec.Height = 720;

        m_FrameBuffer = Cuboid::FrameBuffer::Create(fbSpec);

        m_scActiveScene = CreateRef<Scene>();

        squareEntity = m_scActiveScene->CreateEntity("Yellow Square");
        squareEntity.AddComponent<SpriteRendererComponent>(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));

        auto squareEntity1 = m_scActiveScene->CreateEntity("Yellow Square");
        squareEntity1.AddComponent<SpriteRendererComponent>(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 0.0f));
        auto& square1Tranform = squareEntity1.GetComponent<TransformComponent>();
        square1Tranform = scale;

        CameraEntity = m_scActiveScene->CreateEntity("Camera");
        CameraEntity.AddComponent<CameraComponent>(glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f);

    }

    void CuboidEditor::OnDetach()
    {

    }

    void CuboidEditor::OnUpdate(float dt)
    {

        // Cuboid::RenderCommand::Clear();

        if (m_bIsViewPortFocused || m_bIsViewPortHovered)
        {
            m_CameraController.OnUpdate(dt);
        }
            

        m_FrameBuffer->Bind();
        RenderCommand::SetViewport(0, 0, (uint32_t)m_vcViewPortSize.x, (uint32_t)m_vcViewPortSize.y);

         m_scActiveScene->OnUpdate(dt);

         m_FrameBuffer->UnBind();

         RenderCommand::SetClearColor({ 0.23f, 0.23f, 0.23f, 1.0f });
         RenderCommand::SetViewport(0, 0, (uint32_t)m_vcWindowSize.x, (uint32_t)m_vcWindowSize.y);




    }

    void CuboidEditor::OnImGuiRender()
    {
        auto stats = Cuboid::Renderer2D::GetStats();

        ImGui::Begin("Stats");
        ImGui::Text("Draw calls %d", stats.DrawCalls);
        ImGui::Text("Number of indices %d", stats.GetTotalIndexCount());
        ImGui::Text("Number of vertices %d", stats.GetTotalVertexCount());
        ImGui::Text("Number of quads %d", stats.QuadCount);
        ImGui::End();

        ImGuiWindowFlags windowflags = 0;
        windowflags |= ImGuiWindowFlags_NoScrollWithMouse;
        windowflags |= ImGuiWindowFlags_NoScrollbar;


        
        

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

        ImGui::Begin("Viewport", 0, windowflags);

        m_bIsViewPortFocused = ImGui::IsWindowFocused();
        m_bIsViewPortHovered = ImGui::IsWindowHovered();

     
        Application::Get().GetImGuiLayer()->BlockEvents(!m_bIsViewPortFocused || !m_bIsViewPortHovered);


        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

        if (m_vcViewPortSize != *((glm::vec2*) & viewportPanelSize))
        {
            m_vcViewPortSize = { viewportPanelSize.x, viewportPanelSize.y };
            m_FrameBuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);

            m_CameraController.OnResize(viewportPanelSize.x, viewportPanelSize.y);
            
        }

        ImGui::Image(m_FrameBuffer->GetColorAttachmentRenderID(), { m_vcViewPortSize.x,  m_vcViewPortSize.y });
   

        ImGui::End();

        ImGui::PopStyleVar();


        ImGui::Begin("Properties");

        if (squareEntity)
        {
            ImGui::Separator();

            auto& tag = squareEntity.GetComponent<TagComponent>().Tag;

            ImGui::Text("%s", tag.c_str());

            auto& color = squareEntity.GetComponent<SpriteRendererComponent>().Color;
            ImGui::ColorEdit4("Color ", &color[0]);

            ImGui::Separator();
        }
        ImGui::End();

        Cuboid::Renderer2D::ResetStats();


    }

    void CuboidEditor::OnEvent(Cuboid::Event& event)
    {
        //CUBOID_DEBUG(event.GetName());
       
        EventDispatcher dispatcher(event);

        m_CameraController.OnEvent(event);

        dispatcher.Dispatch<WindowResizeEvent>(CUBOID_BIND_EVENT_FN(CuboidEditor::OnWindowResized));
    }

    CuboidEditor::~CuboidEditor()
    {

    }

    bool CuboidEditor::OnWindowResized(WindowResizeEvent& e)
    {
        m_vcWindowSize = { (float)e.GetWidth(), (float)e.GetHeight() };
        CUBOID_INFO(e.GetHeight());
        CUBOID_INFO(e.GetWidth());

        return true;
    }

}