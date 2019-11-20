#ifndef __MODEL__
#define __MODEL__

#include "Objects/Components/Component.hpp"
#include "Objects/Resources/Mesh.hpp"
#include "Objects/Resources/Texture.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assert.h>

namespace Objects::Components
{
	class Model : public Component
	{
	private:
		std::string directory;
		
		void SetMesh(aiMesh const* m, int n);

		void ProcessNode(aiNode* n, const aiScene* s);
		Resources::Mesh ProcessMesh(aiMesh* m, const aiScene* s);
		std::vector<Resources::Texture> LoadMatTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);

	public:
		Model() = default;
		explicit Model(const std::string& path);
		Model(const Model& m) = default;
		~Model() = default;

		std::vector<Resources::Mesh> m_mesh;
		std::vector<Resources::Texture> m_textures;

		Model& operator=(const Model& m) = default;

		void Update() override {}
		void Start() override {}
	};
}

#endif 