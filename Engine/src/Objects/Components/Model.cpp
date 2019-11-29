#include "Objects/Components/Model.hpp"

namespace Objects::Components
{
	Model::Model(const std::string& path)
	{
		Assimp::Importer importer;

		const aiScene* pScene = importer.ReadFile(path.c_str(), aiProcess_Triangulate |
																aiProcess_GenNormals);

		if (!pScene || pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !pScene->mRootNode)
			std::cout << "error loading " << path << std::endl;

		directory = path.substr(0, path.find_last_of('/'));

		if (pScene)
		{
			aiNode* node = pScene->mRootNode;
			ProcessNode(node, pScene);
		}
	}

	void Model::SetMesh(aiMesh const* m, int n)
	{
		const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

		Resources::Mesh* mesh = &m_mesh[n];

		for (unsigned int i = 0; i < m->mNumVertices; i++) 
		{
			const aiVector3D* pPos = &(m->mVertices[i]);
			const aiVector3D* pNormal = &(m->mNormals[i]) ? &m->mNormals[i] : &Zero3D;
			const aiVector3D* pTexCoord = m->HasTextureCoords(0) ? &(m->mTextureCoords[0][i]) : &Zero3D;

			mesh->vertex.push_back(pPos->x);
			mesh->vertex.push_back(pPos->y);
			mesh->vertex.push_back(pPos->z);
			mesh->vertex.push_back(pNormal->x);
			mesh->vertex.push_back(pNormal->y);
			mesh->vertex.push_back(pNormal->z);
			mesh->vertex.push_back(pTexCoord->x);
			mesh->vertex.push_back(pTexCoord->y);
		}

		for (unsigned int i = 0; i < m->mNumFaces; i++) {
			const aiFace& Face = m->mFaces[i];
			assert(Face.mNumIndices == 3);
			mesh->index.push_back(Face.mIndices[0]);
			mesh->index.push_back(Face.mIndices[1]);
			mesh->index.push_back(Face.mIndices[2]);
		}

		mesh->SetBuffers();


	}

	void Model::ProcessNode(aiNode* n, const aiScene* s)
	{
		for (unsigned int i = 0; i < n->mNumMeshes; i++)
		{
			aiMesh* mesh = s->mMeshes[n->mMeshes[i]];
			m_mesh.push_back(ProcessMesh(mesh, s));
		}
		// then do the same for each of its children
		for (unsigned int i = 0; i < n->mNumChildren; i++)
		{
			ProcessNode(n->mChildren[i], s);
		}
	}

	Resources::Mesh Model::ProcessMesh(aiMesh* m, const aiScene* s)
	{
		Resources::Mesh ret;
		std::vector<Resources::Texture> textures;

		// Walk through each of the mesh's vertices
		for (unsigned int i = 0; i < m->mNumVertices; i++)
		{
			ret.vertex.push_back(m->mVertices[i].x);
			ret.vertex.push_back(m->mVertices[i].y);
			ret.vertex.push_back(m->mVertices[i].z);
			// normals
			ret.vertex.push_back(m->mNormals[i].x);
			ret.vertex.push_back(m->mNormals[i].y);
			ret.vertex.push_back(m->mNormals[i].z);
			// texture coordinates
			if (m->mTextureCoords[0]) // does the m contain texture coordinates?
			{
				ret.vertex.push_back(m->mTextureCoords[0][i].x);
				ret.vertex.push_back(m->mTextureCoords[0][i].y);
			}
			else
			{
				ret.vertex.push_back(0.0f);
				ret.vertex.push_back(0.0f);
			}
			//// tangent
			//vector.x = m->mTangents[i].x;
			//vector.y = m->mTangents[i].y;
			//vector.z = m->mTangents[i].z;
			//vertex.Tangent = vector;
			//// bitangent
			//vector.x = m->mBitangents[i].x;
			//vector.y = m->mBitangents[i].y;
			//vector.z = m->mBitangents[i].z;
			//vertex.Bitangent = vector;
			//vertices.push_back(vertex);
		}
		// now wak through each of the m's faces (a face is a m its triangle) and retrieve the corresponding vertex indices.
		for (unsigned int i = 0; i < m->mNumFaces; i++)
		{
			const aiFace face = m->mFaces[i];
			// retrieve all indices of the face and store them in the indices vector
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				ret.index.push_back(face.mIndices[j]);
		}

		aiMaterial* material = s->mMaterials[m->mMaterialIndex];

		//// 1. diffuse maps
		std::vector<Resources::Texture> diffuseMaps =
			LoadMatTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		//// 2. specular maps
		std::vector<Resources::Texture> specularMaps =
			LoadMatTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		//// 3. normal maps
		std::vector<Resources::Texture> normalMaps = 
			LoadMatTextures(material, aiTextureType_HEIGHT, "texture_normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		//// 4. height maps
		std::vector<Resources::Texture> heightMaps = 
			LoadMatTextures(material, aiTextureType_AMBIENT, "texture_height");
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

		ret.SetBuffers();
		ret.textures = textures;

		// return a m object created from the extracted m data
		return ret;
	}

	std::vector<Resources::Texture> Model::LoadMatTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName)
	{
		std::vector<Resources::Texture> textures;
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);

			std::cout << "on wanna this " << str.C_Str() << std::endl;

			bool skip = false;
			for (unsigned int j = 0; j < m_textures.size(); j++)
			{
				if (std::strcmp(m_textures[j].path.data(), str.C_Str()) == 0)
				{
					textures.push_back(m_textures[j]);
					skip = true;
					break;
				}
			}
			if (!skip)
			{
				Resources::Texture texture(directory + "/" + str.C_Str());
				texture.type = typeName;
				texture.path = str.C_Str();
				textures.push_back(texture);
				m_textures.push_back(texture);
			}
		}
		return textures;
	}
}
