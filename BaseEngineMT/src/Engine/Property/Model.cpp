#include "Engine/Property/Model.hpp"
#include <iostream>
#include <sstream>



Core::Model::Model(std::string path)
{
	Assimp::Importer importer;

	const aiScene* pScene = importer.ReadFile(path, aiProcess_Triangulate |
													aiProcess_GenNormals);

	if (!pScene || pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !pScene->mRootNode)
		std::cout << "error loading " << path << std::endl;

	m_directoryBis = m_fullpath = path;
	m_directoryBis = (m_directoryBis.substr(0, m_directoryBis.find_last_of('/')));

	
	
	if (pScene)
	{
		aiNode* node = pScene->mRootNode;
		ProcessNode(node, pScene);
	}
}



void Core::Model::ProcessNode(aiNode* n, const aiScene* s)
{
	for (unsigned int i = 0; i < n->mNumMeshes; i++)
	{
		aiMesh* mesh = s->mMeshes[n->mMeshes[i]];
		m_mesh.push_back(std::make_pair<Core::Mesh, bool>(ProcessMesh(mesh, s), false));
	}

	for (unsigned int i = 0; i < n->mNumChildren; i++)
	{
		ProcessNode(n->mChildren[i], s);
	}
}



Core::Mesh Core::Model::ProcessMesh(aiMesh* m, const aiScene* s)
{
	Core::Mesh ret;
	std::vector<Texture> textures;

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
	numVertex = m->mNumVertices;
	numFace = m->mNumFaces;

	aiMaterial* material = s->mMaterials[m->mMaterialIndex];

	//// 1. diffuse maps
	std::vector<Texture> diffuseMaps =
		LoadMatTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	//// 2. specular maps
	std::vector<Texture> specularMaps =
		LoadMatTextures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	//// 3. normal maps
	std::vector<Texture> normalMaps =
		LoadMatTextures(material, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	//// 4. height maps
	std::vector<Texture> heightMaps =
		LoadMatTextures(material, aiTextureType_AMBIENT, "texture_height");
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	ret.textures = textures;

	// return a m object created from the extracted m data
	return ret;
}



std::vector<Texture> Core::Model::LoadMatTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);

		bool skip = false;
		for (auto& texture : m_textures)
		{
			if (std::strcmp(texture.path.data(), str.C_Str()) == 0)
			{
				textures.push_back(texture);
				skip = true;
				break;
			}
		}
		
		if (!skip)
		{
			Texture texture(m_directoryBis + "/" + str.C_Str());
			texture.type = typeName;
			//texture.path = str.C_Str();
			textures.push_back(texture);
			m_textures.push_back(texture);
		}
	}
	return textures;
}



void Core::Model::BindMeshs()
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



void Core::Model::Draw(unsigned int s)
{
	BindMeshs();

	for (auto& mesh : m_mesh)
	{
		// bind appropriate textures
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;

		int i = 0;

		for (auto& texture : mesh.first.textures)
		{
			glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
			// retrieve texture number (the N in diffuse_textureN)
			std::string number;
			std::string name = texture.type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++); // transfer unsigned int to stream
			else if (name == "texture_normal")
				number = std::to_string(normalNr++); // transfer unsigned int to stream
			else if (name == "texture_height")
				number = std::to_string(heightNr++); // transfer unsigned int to stream

													 // now set the sampler to the correct texture unit
			glUniform1i(glGetUniformLocation(s, ("material." + name + number).c_str()), i);
			// and finally bind the texture
			texture.Use();

			i++;
		}

		// draw mesh
		glBindVertexArray(mesh.first.VAO);
		glDrawElements(GL_TRIANGLES, mesh.first.index.size(), GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);

		// always good practice to set everything back to defaults once configured.
		glActiveTexture(GL_TEXTURE0);
	}
}