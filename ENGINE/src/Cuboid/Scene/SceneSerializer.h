#pragma once
#include "Scene.h"
#include "Cuboid/Core/Core.h"

namespace Cuboid
{

	class SceneSerializer
	{
	public:
		SceneSerializer(const Ref<Scene>& scene);

		void Serialize(const std::string& path);
		void SerializeRuntime(const std::string& path);

		bool Deserialize(const std::string& path);
		bool DeserializeRuntime(const std::string& path);

	private:

		Ref<Scene> m_Scene;
	};

}