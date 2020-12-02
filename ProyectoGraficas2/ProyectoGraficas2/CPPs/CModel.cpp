#include "..\Includes\CModel.h"
#include "..\Includes\CGraphicApi.h"

void CModel::Init(std::string const& _path, CGraphicApi* _graphicApi){

	//Read _file via assimp
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(_path,
		aiProcessPreset_TargetRealtime_Fast |
		aiProcess_ConvertToLeftHanded |
		aiProcess_FindInstances |
		aiProcess_ValidateDataStructure |
		aiProcess_OptimizeMeshes |
		aiProcess_Debone);

	//Check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){

		return;
	}

	//Retrieve the directory path of the _file
	m_directory = _path.substr(0, _path.find_last_of('/'));

	//Process assimp's root node recursively
	ProcessNode(scene->mRootNode, scene, _graphicApi);

	//Create texture sampler for model's textures
	m_sampler.push_back(_graphicApi->CreateSamplerState());
}

void CModel::Draw(CGraphicApi* _graphicApi){

	for (unsigned int i = 0; i < m_meshes.size(); i++){

		m_meshes[i]->Draw(_graphicApi, m_sampler);
	}
}

void CModel::ProcessNode(aiNode* _node, 
	const aiScene* _scene,
	CGraphicApi* _graphicApi){

	//Process each _mesh located at the current node
	for (unsigned int i = 0; i < _node->mNumMeshes; i++){

		//The node object only contains indices to index the actual objects in the scene.
		//The scene contains all the data, node is just to keep stuff organized.
		aiMesh* _mesh = _scene->mMeshes[_node->mMeshes[i]];
		m_meshes.push_back(ProcessMesh(_mesh, _scene, _graphicApi));
	}

	for (unsigned int i = 0; i < _node->mNumChildren; i++){

		ProcessNode(_node->mChildren[i], _scene, _graphicApi);
	}
}

CMesh* CModel::ProcessMesh(aiMesh* _mesh, 
	const aiScene* _scene,
	CGraphicApi* _graphicApi){

	//Data to fill
	std::vector<Vertex>* vertices = new std::vector<Vertex>();
	std::vector<unsigned int>* indices = new std::vector<unsigned int>();
	std::vector<Texture> textures;

	//Walk through each of the _mesh's vertices.
	for (unsigned int i = 0; i < _mesh->mNumVertices; i++){

		Vertex structVertex;

		//Positions
		structVertex.position.x = _mesh->mVertices[i].x;
		structVertex.position.y = _mesh->mVertices[i].y;
		structVertex.position.z = _mesh->mVertices[i].z;

		//Texcoords
		//Check if _mesh contains texcoords
		if (_mesh->mTextureCoords[0]){

			structVertex.texCoords.x = _mesh->mTextureCoords[0][i].x;
			structVertex.texCoords.y = _mesh->mTextureCoords[0][i].y;
		}
		else{

			structVertex.texCoords = glm::vec2(0.0f, 0.0f);
		}

		//Normals
		structVertex.normal.x = _mesh->mNormals[i].x;
		structVertex.normal.y = _mesh->mNormals[i].y;
		structVertex.normal.z = _mesh->mNormals[i].z;

		//Tangents
		structVertex.tangent.x = _mesh->mTangents[i].x;
		structVertex.tangent.y = _mesh->mTangents[i].y;
		structVertex.tangent.z = _mesh->mTangents[i].z;

		//Bitangents
		structVertex.tangent.x = _mesh->mBitangents[i].x;
		structVertex.tangent.y = _mesh->mBitangents[i].y;
		structVertex.tangent.z = _mesh->mBitangents[i].z;

		vertices->push_back(structVertex);
	}

	//Go through each of the _mesh's faces and retrieve the corresponding indices.
	for (unsigned int i = 0; i < _mesh->mNumFaces; i++){

		aiFace face = _mesh->mFaces[i];
		//retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++){

			indices->push_back(face.mIndices[j]);
		}
	}

	aiMaterial* material = _scene->mMaterials[_mesh->mMaterialIndex];

	std::vector<Texture> diffuseMaps = LoadMaterialTextures(material,
		aiTextureType_DIFFUSE,
		_graphicApi);

	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

	CMesh* newMesh = new CMesh();
	newMesh->Init(vertices, indices, textures, _graphicApi);

	return newMesh;
}

std::vector<Texture> CModel::LoadMaterialTextures(aiMaterial* _mat, 
	aiTextureType _type,
	CGraphicApi* _graphicApi){

	std::vector<Texture> textures;

	for (unsigned int i = 0; i < _mat->GetTextureCount(_type); i++){

		aiString aistr;

		_mat->GetTexture(_type, i, &aistr);

		std::string srcFile = std::string(aistr.C_Str());

		srcFile = m_directory + GetTexturePath(srcFile);

		bool skip = false;

		for (unsigned int j = 0; j < m_textures.size(); j++){

			if (std::strcmp(m_textures[j].path.data(), srcFile.data()) == 0){

				textures.push_back(m_textures[j]);
				skip = true;
				break;
			}
		}
		if (!skip){

			Texture meshTexture;
			meshTexture.texture = _graphicApi->LoadTextureFromFile(srcFile);
			meshTexture.path = srcFile;
			textures.push_back(meshTexture);
			m_textures.push_back(meshTexture);
		}
	}

	return textures;
}

std::string CModel::GetTexturePath(std::string _file){

	size_t realPos = 0;
	size_t posInvSlash = _file.rfind('\\');
	size_t posSlash = _file.rfind('/');

	if (posInvSlash == std::string::npos){

		if (posSlash != std::string::npos){

			realPos = posSlash;
		}
	}
	else{

		realPos = posInvSlash;

		if (!posSlash == std::string::npos){

			if (posSlash > realPos){

				posSlash = realPos;
			}
		}
	}

	return _file.substr(realPos, _file.length() - realPos);
}
