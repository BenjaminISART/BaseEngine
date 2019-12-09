#ifndef __MODEL__
#define __MODEL__

#include "Engine/Property/Property.hpp"
#include "Engine/Property/Mesh.hpp"
#include "Engine/Property/Shader.hpp"
#include "Engine/Property/Texture.hpp"
#include <utility>
#include <iostream>
#include <atomic>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <vector>

namespace Core
{
	class Model : public Property
	{
	private:

#pragma region private attributes
		const char* m_directory;
		std::string m_directoryBis;

		std::vector<std::pair<Core::Mesh, bool>> m_mesh;
		std::vector<Texture> m_textures;
#pragma endregion

#pragma region private methods
		// Assimp Loading
		void ProcessNode(aiNode* n, const aiScene* s);
		Core::Mesh ProcessMesh(aiMesh* m, const aiScene* s);
		std::vector<Texture> LoadMatTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
#pragma endregion

	public:

		Model() : m_directory {nullptr} {}; // CTOR
		Model(std::string path);
		// Model(Model const& c); // CPY CTOR
		// Model(Model const && c); // MV CTOR
		~Model() = default; // DTOR

#pragma region public attributes
#pragma endregion

#pragma region public methods
		void BindMeshs();

		void Draw(unsigned int s);
#pragma endregion
	};
}

#endif // __MODEL__