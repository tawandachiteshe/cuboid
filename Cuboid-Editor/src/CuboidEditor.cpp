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


#if 1
        m_Va = Cuboid::VertexArray::Create();

        m_Texture = Cuboid::Texture2D::Create(1, 1);

        m_Texture2 = Cuboid::Texture2D::Create(1, 1);



        uint32_t textureData[] = { 0xFF00FF00u, 0xFF0000FFu, 0xFF00FF00u, 0xFF0000FFu };

        uint32_t textureData2 = 0xFF0000FFu;

        m_Texture->SetData(textureData, sizeof(textureData));
        m_Texture2->SetData(&textureData2, sizeof(textureData));

        m_TextureArray = Cuboid::Texture2DArray::Create(2);

        m_TextureArray->AddTexture(m_Texture);
        m_TextureArray->AddTexture(m_Texture2);

        Vertex vertices[] =
        {
            { {-1.5f, -1.5f, 0.0f }, { 255, 0, 0, 255 }, { 0.0f, 0.0f }, 1 },
            { { 1.5f, -1.5f, 0.0f  }, { 0, 0, 255, 255 }, { 0.0f, 1.0f }, 0 },
            { { 1.5f, 1.5f, 0.0f }, { 0, 255, 0, 255 },  { 1.0f, 0.0f }, 1 },
            { {-1.5f, 1.5f, 0.0f }, { 0 , 255, 255, 255 },  { 1.0f, 1.0f }, 0 }
        };

        m_vb = Cuboid::VertexBuffer::Create(sizeof(vertices));
        m_vb->SetData(vertices, sizeof(vertices));
        m_Shader = Cuboid::Shader::FromShaderSourceFiles("res/Shaders/FlatColorPixelShader.hlsl", "res/Shaders/FlatColorVertexShader.hlsl");

        m_vb->SetShader(m_Shader);

        m_TextureArray->Bind(0);

        m_vb->SetLayout({ { Cuboid::ShaderDataType::Float3, "a_Position" }, { Cuboid::ShaderDataType::Byte4, "a_Color" }, { Cuboid::ShaderDataType::Float2, "a_Texcoord" }, { Cuboid::ShaderDataType::Int, "a_textureidx" } });

        m_Va->AddVertexBuffer(m_vb);

        m_vb->Bind();
        uint32_t indices[] = { 0, 1, 2, 0, 2, 3 };
        m_ib = Cuboid::IndexBuffer::Create(indices, 6);

        m_Va->SetIndexBuffer(m_ib);

#endif

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
        Cuboid::RenderCommand::SetViewport(0, 0, (uint32_t)m_vcViewPortSize.x, (uint32_t)m_vcViewPortSize.y);

        const auto& scale = glm::scale(glm::mat4(1.0f), glm::vec3(xscale, yscale, 1.0f));

        Cuboid::Renderer::BeginScene(m_CameraController.GetCamera());

        Cuboid::Renderer::Submit(m_Va, m_Shader);

        Cuboid::Renderer::EndScene();

        Cuboid::Renderer2D::BeginScene(m_CameraController.GetCamera());

        Cuboid::Renderer2D::DrawQuad({ -1.5f, -1.5f }, { 2.0f, 2.0f }, { 1.0f, 0.0f, 0.0f, 1.0f });

        Cuboid::Renderer2D::DrawQuad({ 0.5f, 0.5f }, { 2.0f, 2.0f }, { 1.0f, 0.0f, 1.0f, 1.0f });

        Cuboid::Renderer2D::DrawQuad({ 0.75f, 0.75f }, { 2.0f, 2.0f }, { 0.0f, 0.0f, 1.0f, 1.0f });

        Cuboid::Renderer2D::DrawQuad({ 1.0f, 0.0f }, { 2.0f, 2.0f });

        rot += dt * 45.f;

        Cuboid::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f }, { 4.0f, 4.0f }, rot, SquareColor);

        Cuboid::Renderer2D::EndScene();

        m_FrameBuffer->UnBind();

        Cuboid::RenderCommand::SetClearColor({ 0.23f, 0.23f, 0.23f, 1.0f });
        Cuboid::RenderCommand::SetViewport(0, 0, (uint32_t)m_vcWindowSize.x, (uint32_t)m_vcWindowSize.y);




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

        ImGui::ColorEdit4("Rotated square color ", &SquareColor[0]);

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