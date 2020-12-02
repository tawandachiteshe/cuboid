#include "CuboidEditor.h"
#include "imgui.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Cuboid/Scene/SceneSerializer.h>
#include "Cuboid/Utils/IO/MeshLoader.h"

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
        auto constbuffer = CreateRef<ConstantBuffer>();

        struct Spot
        {
            glm::vec4 Color;
            glm::vec4 Color1;
            glm::vec4 Color2;
            glm::vec4 Color3;
        };

        struct PIXEL_DIRECTIONAL_LIGHT_DATA
        {
            glm::vec3 mesh_color;
            glm::vec3 light_dir;
            glm::vec3 light_color;
            glm::vec3 padding;
        };

        struct MVP
        {
           glm::mat4 transform;
          glm::mat4 projectionview;
          glm::mat4 inverseTranposeTransform;

        };




        constbuffer->AddConstantBuffer<MVP>("MVP", ConstantBuffer::ConstantBufferType::VERTEX_SHADER_CONSTANT_BUFFER);
        constbuffer->AddConstantBuffer<Spot>("Color", ConstantBuffer::ConstantBufferType::PIXEL_SHADER_CONSTANT_BUFFER);
        constbuffer->AddConstantBuffer<PIXEL_DIRECTIONAL_LIGHT_DATA>("Light", ConstantBuffer::ConstantBufferType::PIXEL_SHADER_CONSTANT_BUFFER);

        constbuffer->SetConstantBufferData<Spot>("Color", [](Spot* spot)
            {

                spot->Color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
                spot->Color1 = glm::vec4(1.0f, 0.22f, 0.23f, 1.0f);
                spot->Color2 = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
                spot->Color3 = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);

            });

        constbuffer->SetConstantBufferData<PIXEL_DIRECTIONAL_LIGHT_DATA>("Light", [](PIXEL_DIRECTIONAL_LIGHT_DATA* light)
            {
                DirectionalLight d_light;
                d_light.m_Color = { 0.0, 1.0, 0.0f };
                d_light.m_Direction = { -1.0f, 0.0f, 0.0f };
                d_light.m_Intensity = 1.0f;

                light->mesh_color = { 0.23, 1.0f, 0.9f };
                light->light_color = d_light.GetLightColor();
                light->light_dir = d_light.GetDirection();
                light->padding = { 1.0f, 1.0f, 1.0f };

            });

        m_MeshShader = Shader::FromShaderSourceFiles("res/Shaders/MeshRenderingPixel.hlsl", "res/Shaders/MeshRenderingVert.hlsl");

        m_MeshShader->SetConstantBuffer(constbuffer);

        auto vertex_array = VertexArray::Create();

        auto mesh = MeshLoader("res/models/torus.fbx").GetMeshes().at(0);
        mesh.SetVertexArray(vertex_array);
        mesh.GetVertexBuffer()->SetShader(m_MeshShader);

        mesh.GetVertexBuffer()->SetLayout(
            { {ShaderDataType::Float3, "a_Position"},
              {ShaderDataType::Float2, "a_TextureCoord"},
              {ShaderDataType::Float3, "a_Normals"}
            
            });

        

        vertex_array->AddVertexBuffer(mesh.GetVertexBuffer());
        vertex_array->SetIndexBuffer(mesh.GetIndexBuffer());

        Cuboid::FrameBufferSpecification fbSpec;

        fbSpec.Width = 1280;
        fbSpec.Height = 720;

        m_FrameBuffer = Cuboid::FrameBuffer::Create(fbSpec);
        m_scActiveScene = CreateRef<Scene>();


#if 1
        m_CubeEntity = m_scActiveScene->CreateEntity("White Cube");
        m_CubeEntity.AddComponent<MeshRendererComponent>(mesh, m_MeshShader);

        squareEntity = m_scActiveScene->CreateEntity("Yellow Square");
        squareEntity.AddComponent<SpriteRendererComponent>(glm::vec4(1.0f, 1.0f, 0.0f, 0.65f));

        auto squareEntity1 = m_scActiveScene->CreateEntity("Bigger Square");
        squareEntity1.AddComponent<SpriteRendererComponent>(glm::vec4(1.0f, 0.0f, 0.0f, 0.65f));

        auto& square1Tranform = squareEntity1.GetComponent<TransformComponent>();
        square1Tranform.Scale = glm::vec3(2.0f, 2.0f, 1.0f);

        CameraEntity = m_scActiveScene->CreateEntity("Camera");
        CameraEntity.AddComponent<CameraComponent>();
 
        class CameraController : ScriptableEntity
        {
        public:

            void OnCreate()
            {
          
                CUBOID_DEBUG("Script init");

            }

            void OnDestroy()
            {

            }

            void OnUpdate(float ts)
            {
          

                auto& transform = GetComponent<TransformComponent>();
                float speed = 5.0f;

                if (Input::IsKeyPressed(Key::A))
                {
                    transform.Translation.x -= speed * ts;
                }
                else if (Input::IsKeyPressed(Key::D))
                {
                    transform.Translation.x += speed * ts;
                }
                else if (Input::IsKeyPressed(Key::W))
                {
                    transform.Translation.y += speed * ts;
                }
                else if (Input::IsKeyPressed(Key::S))
                {
                    transform.Translation.y -= speed * ts;
                }
       
            }


        };


        CameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();
        squareEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();

#endif
        m_SceneHieracyPanel.SetContext(m_scActiveScene);
        //SceneSerializer serializer(m_scActiveScene);
       // serializer.DeserializeRuntime("res/scenes/DefaultScene.buboid");

        
    }

    void CuboidEditor::OnDetach()
    {

    }

    static float sdt = 0.0f;

    void CuboidEditor::OnUpdate(float dt)
    {
        sdt = dt;
        
        m_FrameBuffer->Bind();
        RenderCommand::SetViewport(0, 0, (uint32_t)m_vcViewPortSize.x, (uint32_t)m_vcViewPortSize.y);

        if (m_bIsViewPortFocused || m_bIsViewPortHovered)
        {
            
        }

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
        float fps = 1.0f / sdt;
        ImGui::Text("Frames per second %d", (uint32_t)fps);
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

            m_scActiveScene->OnViewportResize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
            
        }

        ImGui::Image(m_FrameBuffer->GetColorAttachmentRenderID(), { m_vcViewPortSize.x,  m_vcViewPortSize.y });
   

        ImGui::End();

        ImGui::PopStyleVar();


        m_SceneHieracyPanel.OnImGuiRender();

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
        return false;
    }

}