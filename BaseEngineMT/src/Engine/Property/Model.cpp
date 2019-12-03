#include "Engine/Property/Model.hpp"
#include <iostream>



Core::Model::Model(std::string path)
{
	Assimp::Importer importer;

	const aiScene* pScene = importer.ReadFile(path, aiProcess_Triangulate |
													aiProcess_GenNormals);

	if (!pScene || pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !pScene->mRootNode)
		std::cout << "error loading " << path << std::endl;

	m_directory = std::string(path).substr(0, std::string(path).find_last_of('/')).c_str();

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
	//std::vector<Core::Texture> textures;

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

	//aiMaterial* material = s->mMaterials[m->mMaterialIndex];

	////// 1. diffuse maps
	//std::vector<Core::Texture> diffuseMaps =
	//	LoadMatTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	//textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	////// 2. specular maps
	//std::vector<Core::Texture> specularMaps =
	//	LoadMatTextures(material, aiTextureType_SPECULAR, "texture_specular");
	//textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	////// 3. normal maps
	//std::vector<Core::Texture> normalMaps =
	//	LoadMatTextures(material, aiTextureType_HEIGHT, "texture_normal");
	//textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	////// 4. height maps
	//std::vector<Core::Texture> heightMaps =
	//	LoadMatTextures(material, aiTextureType_AMBIENT, "texture_height");
	//textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	//ret.textures = textures;

	// return a m object created from the extracted m data
	return ret;
}