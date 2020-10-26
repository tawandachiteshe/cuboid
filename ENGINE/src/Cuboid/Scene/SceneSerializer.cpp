#include "SceneSerializer.h"
#include <yaml-cpp/yaml.h>
#include "Entity.h"
#include "Components.h"

namespace YAML
{
    template<>
    struct convert<glm::vec3>
    {
        static Node encode(const glm::vec3& rhs)
        {

            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);

            return node;

        }

        static bool decode(const Node& node, glm::vec3& rhs)
        {
            if (!node.IsSequence() || node.size() != 3)
                return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();

            return true;
            
        }

    };

    template<>
    struct convert<glm::vec4>
    {
        static Node encode(const glm::vec4& rhs)
        {

            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.push_back(rhs.w);

            return node;

        }

        static bool decode(const Node& node, glm::vec4& rhs)
        {
            if (!node.IsSequence() || node.size() != 4)
                return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            rhs.w = node[3].as<float>();

            return true;

        }

    };
}

namespace Cuboid
{

    YAML::Emitter& operator<<(YAML::Emitter& out, glm::vec3& values)
    {

        out << YAML::Flow;
        out << YAML::BeginSeq << values.x << values.y << values.z << YAML::EndSeq;
        return out;

    }

    YAML::Emitter& operator<<(YAML::Emitter& out, glm::vec4& values)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << values.x << values.y << values.z << values.w << YAML::EndSeq;
        return out;
    }

    SceneSerializer::SceneSerializer(const Ref<Scene>& scene) :
        m_Scene(scene)
    {
    }

    static void SerializeEntity(YAML::Emitter& out, Entity entity)
    {

        out << YAML::BeginMap;
        out << YAML::Key << "Entity" << YAML::Value << "127189218913";
        

        if (entity.HasComponent<TagComponent>())
        {

            out << YAML::Key << "TagComponent";
            out << YAML::BeginMap;
            out << YAML::Key << "Tag" << YAML::Value << entity.GetComponent<TagComponent>().Tag;
            out << YAML::EndMap;


        }

        if (entity.HasComponent<TransformComponent>())
        {

            out << YAML::Key << "TransformComponent";
            out << YAML::BeginMap;

            auto& tc = entity.GetComponent<TransformComponent>();

            out << YAML::Key << "Translation" << YAML::Value << tc.Translation;
            out << YAML::Key << "Rotation" << YAML::Value << tc.Rotation;
            out << YAML::Key << "Scale" << YAML::Value << tc.Scale;

            out << YAML::EndMap;


        }


        if (entity.HasComponent<CameraComponent>())
        {
            auto& cameraComponent = entity.GetComponent<CameraComponent>();
            auto& camera = cameraComponent.Camera;

            out << YAML::Key << "CameraComponent";
            out << YAML::BeginMap;

            out << YAML::Key << "Camera";
            out << YAML::BeginMap;

            out << YAML::Key << "ProjectionType" << (int)camera.GetCameraProjectionType();
            out << YAML::Key << "PerspectiveFOV" << camera.GetPerspectiveVerticalFOV();
            out << YAML::Key << "PerspectiveNear" << camera.GetPerspectiveNearClip();
            out << YAML::Key << "PerspectiveFar" << camera.GetPerspectiveFarClip();

            out << YAML::Key << "OrthographicSize" << camera.GetOrthographicSize();
            out << YAML::Key << "OrthographicNear" << camera.GetOrthoGraphicNearClip();
            out << YAML::Key << "OrthographicFar" << camera.GetPerspectiveFarClip();

            out << YAML::EndMap;

            out << YAML::Key << "Primary" << YAML::Value << cameraComponent.Primary;
            out << YAML::Key << "FixedAspect" << YAML::Value << cameraComponent.FixedAspectRatio;

            out << YAML::EndMap;


        }


        if (entity.HasComponent<SpriteRendererComponent>())
        {

            out << YAML::Key << "SpriteRendererComponent";
            out << YAML::BeginMap;
            out << YAML::Key << "Color" << YAML::Value << entity.GetComponent<SpriteRendererComponent>().Color;
            out << YAML::EndMap;

        }

        out << YAML::EndMap;

    }

    void SceneSerializer::Serialize(const std::string& path)
    {
        YAML::Emitter out;

        out << YAML::BeginMap;
        out << YAML::Key << "Scene" << YAML::Value << "Untitled";
        out << YAML::Key << "Entities" << YAML::BeginSeq;

        m_Scene->m_Registry.each([&](auto entityID)
        {
                Entity entity{ entityID, m_Scene.get() };

                if (!entity)
                    return;

                SerializeEntity(out, entity);

        });

        out << YAML::EndSeq;
        out << YAML::EndMap;

        std::ofstream fout(path);
        fout << out.c_str();
        fout.close();
    }


    static void SerializeEntityRuntime(std::ofstream& fout, Entity entity)
    {

        if (entity.HasComponent<TagComponent>())
        {

            auto& tag = entity.GetComponent<TagComponent>().Tag;
            fout.write(tag.c_str(), tag.size() * sizeof(char));

        }

        if (entity.HasComponent<TransformComponent>())
        {


            auto& tc = entity.GetComponent<TransformComponent>();
            fout.write((char*)&tc.Translation, sizeof(float) * 3);
            fout.write((char*)&tc.Rotation, sizeof(float) * 3);
            fout.write((char*)&tc.Scale, sizeof(float) * 3);

        }

        if (entity.HasComponent<CameraComponent>())
        {
            auto& cameraComponent = entity.GetComponent<CameraComponent>();
            auto& camera = cameraComponent.Camera;

            fout << (int)camera.GetCameraProjectionType();
            fout << camera.GetPerspectiveVerticalFOV();
            fout <<  camera.GetPerspectiveNearClip();
            fout << camera.GetPerspectiveFarClip();

            fout << camera.GetOrthographicSize();
            fout << camera.GetOrthoGraphicNearClip();
            fout << camera.GetPerspectiveFarClip();

            fout << cameraComponent.Primary;
            fout << cameraComponent.FixedAspectRatio;


        }

        if (entity.HasComponent<SpriteRendererComponent>())
        {
            
            fout.write((char*)&entity.GetComponent<SpriteRendererComponent>().Color, sizeof(float) * 3);

        }


    }


    void SceneSerializer::SerializeRuntime(const std::string& path)
    {
        std::ofstream fout(path, std::ios::binary);
        m_Scene->m_Registry.each([&](auto entityID)
        {
            Entity entity{ entityID, m_Scene.get() };

            if (!entity)
               return;

            SerializeEntityRuntime(fout, entity);

         });

        fout.close();
        

    }

    bool SceneSerializer::Deserialize(const std::string& path)
    {

        YAML::Node data = YAML::LoadFile(path);

        if (!data["Scene"])
            return false;

        std::string scenename = data["Scene"].as<std::string>();
        CUBOID_CORE_INFO("Deserializing scene '{0}'", scenename);

        auto entities = data["Entities"];

        if (entities)
        {

            for (auto entity : entities)
            {
                uint64_t uuid = entity["Entity"].as<uint64_t>();
                std::string name;

                auto tagComponent = entity["TagComponent"];

                if (tagComponent)
                {

                    name = tagComponent["Tag"].as<std::string>();
                    CUBOID_CORE_INFO("Deserializing Entity witd ID = {0} and Name = {1}", uuid, name);

                }

                Entity deserializedEntity = m_Scene->CreateEntity(name);

                auto tranformComponent = entity["TransformComponent"];
                if (tranformComponent)
                {
                    auto& tc = deserializedEntity.GetComponent<TransformComponent>();
                    tc.Translation = tranformComponent["Translation"].as<glm::vec3>();
                    tc.Rotation = tranformComponent["Rotation"].as<glm::vec3>();
                    tc.Scale = tranformComponent["Scale"].as<glm::vec3>();

                }

                auto cameraComponent = entity["CameraComponent"];
                if (cameraComponent)
                {

                    auto& cc = deserializedEntity.AddComponent<CameraComponent>();

                    auto& cameraProps = cameraComponent["Camera"];
                    cc.Camera.SetCameraProjectionType((SceneCamera::CameraProjectionType) cameraProps["ProjectionType"].as<int>());
                    cc.Camera.SetPerspectiveVerticalFOV(cameraProps["PerspectiveFOV"].as<float>());
                    cc.Camera.SetPerspectiveNearClip(cameraProps["PerspectiveNear"].as<float>());
                    cc.Camera.SetPerspectiveFarClip(cameraProps["PerspectiveFar"].as<float>());

                    cc.Camera.SetOrthographicSize(cameraProps["OrthographicSize"].as<float>());
                    cc.Camera.SetOrthoGraphicNearClip(cameraProps["OrthographicNear"].as<float>());
                    cc.Camera.SetOrthoGraphicFarClip(cameraProps["OrthographicFar"].as<float>());

                    cc.Primary = cameraComponent["Primary"].as<bool>();
                    cc.FixedAspectRatio = cameraComponent["FixedAspect"].as<bool>();
                    

                }


                auto spriteRendererComponent = entity["SpriteRendererComponent"];

                if (spriteRendererComponent)
                {

                    auto& src = deserializedEntity.AddComponent<SpriteRendererComponent>();
                    src.Color = spriteRendererComponent["Color"].as<glm::vec4>();


                }

            }

        }


        return true;
    }

    bool SceneSerializer::DeserializeRuntime(const std::string& path)
    {

        return false;
    }
}