#ifndef __MODEL__
#define __MODEL__

#include "Engine/Property/Property.hpp"
#include "Engine/Property/Mesh.hpp"
#include <utility>
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

		std::vector<std::pair<Core::Mesh, bool>> m_mesh;
		//std::vector<Resources::Texture> m_textures;
#pragma endregion

#pragma region private methods
		void ProcessNode(aiNode* n, const aiScene* s);
		Core::Mesh ProcessMesh(aiMesh* m, const aiScene* s);
		//std::vector<Resources::Texture> LoadMatTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
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
		void BindMeshs()
		{
			for (auto& p : m_mesh)
			{
				// test if the mesh's buffers has been binded
				if (!p.second)
				{
					p.second = true;
					p.first.SetBuffers();
				}
			}
		}

		void Draw()
		{
			BindMeshs();

			for (auto& mesh : m_mesh)
			{
				// bind appropriate textures
				unsigned int diffuseNr = 1;
				unsigned int specularNr = 1;
				unsigned int normalNr = 1;
				unsigned int heightNr = 1;
				//for (unsigned int i = 0; i < textures.size(); i++)
				//{
				//	glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
				//	// retrieve texture number (the N in diffuse_textureN)
				//	std::string number;
				//	std::string name = textures[i].type;
				//	if (name == "texture_diffuse")
				//		number = std::to_string(diffuseNr++);
				//	else if (name == "texture_specular")
				//		number = std::to_string(specularNr++); // transfer unsigned int to stream
				//	else if (name == "texture_normal")
				//		number = std::to_string(normalNr++); // transfer unsigned int to stream
				//	else if (name == "texture_height")
				//		number = std::to_string(heightNr++); // transfer unsigned int to stream

				//											 // now set the sampler to the correct texture unit
				//	glUniform1i(glGetUniformLocation(s.ID(), ("material." + name + number).c_str()), i);
				//	// and finally bind the texture
				//	glBindTexture(GL_TEXTURE_2D, textures[i].m_ID);
				//}

				// draw mesh
				glBindVertexArray(mesh.first.VAO);
				glDrawElements(GL_TRIANGLES, mesh.first.index.size(), GL_UNSIGNED_INT, nullptr);
				glBindVertexArray(0);

				// always good practice to set everything back to defaults once configured.
				glActiveTexture(GL_TEXTURE0);
			}
		}
#pragma endregion
	};
}

#endif // __MODEL__