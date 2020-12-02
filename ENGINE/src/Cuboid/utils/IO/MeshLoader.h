#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Cuboid/Renderer/Mesh.h"

namespace Cuboid
{

	class MeshLoader
	{

	public:
		MeshLoader(const std::string& filename);
		std::vector<Mesh>& GetMeshes() { return m_Meshes; }

	private:

		std::vector<Mesh> m_Meshes;

		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	};

}