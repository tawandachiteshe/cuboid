#include "MeshLoader.h"


namespace Cuboid
{
	MeshLoader::MeshLoader(const std::string& filename)
	{
		Assimp::Importer importer;

		const aiScene* pScene = importer.ReadFile(filename, aiProcess_Triangulate);

		CUBOID_ASSERT(pScene, "Unable to load models from file");
		ProcessNode(pScene->mRootNode, pScene);

	}

	void MeshLoader::ProcessNode(aiNode* node, const aiScene* scene)
	{

		for (uint32_t i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_Meshes.push_back(this->ProcessMesh(mesh, scene));
		}

		for (uint32_t i = 0; i < node->mNumChildren; i++)
		{
			this->ProcessNode(node->mChildren[i], scene);
		}

	}

	Mesh MeshLoader::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		// Data to fill
		std::vector<VERTEX> vertices;
		std::vector<uint32_t> indices;

		//TODO i will care later
		/*
		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];

			if (textype.empty()) textype = determineTextureType(scene, mat);
		}
		*/

		// Walk through each of the mesh's vertices
		for (uint32_t i = 0; i < mesh->mNumVertices; i++)
		{
			VERTEX vertex;

			vertex.positions = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);

			
			if (mesh->mTextureCoords[0])
			{
				vertex.texcoords = { (float)mesh->mTextureCoords[0][i].x, (float)mesh->mTextureCoords[0][i].y };
			}
			
			if (mesh->HasNormals())
			{
				vertex.normals = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].y };
			}
			/*
			if (mesh->HasVertexColors(i))
			{
				vertex.colors = { mesh->mColors[i]->r, mesh->mColors[i]->b , mesh->mColors[i]->g, mesh->mColors[i]->a };
			}

			*/
			vertices.push_back(vertex);
		}

		for (uint32_t i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];

			for (uint32_t j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		/*
		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

			vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", scene);
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		}

		*/

		return Mesh(vertices, indices);
	}
}