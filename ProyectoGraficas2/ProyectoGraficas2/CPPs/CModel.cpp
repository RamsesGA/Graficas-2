#include <iostream>
#include "..\Includes\CModel.h"
#include "..\Includes\CGraphicApi.h"

/*

void CModel::LoadModel(std::string _path){

    Assimp::Importer import;

    const aiScene* scene = import.ReadFile(_path, 
        aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || 
        scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || 
        !scene->mRootNode){

        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }

    m_directory = _path.substr(0, _path.find_last_of('/'));

    ProcessNode(scene->mRootNode, scene);
}

void CModel::ProcessNode(aiNode* _node, 
    const aiScene* _scene){

    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < _node->mNumMeshes; i++){

        aiMesh* _mesh = _scene->mMeshes[_node->mMeshes[i]];
        m_meshes.push_back(ProcessMesh(_mesh, _scene));
    }

    // then do the same for each of its children
    for (unsigned int i = 0; i < _node->mNumChildren; i++){

        ProcessNode(_node->mChildren[i], _scene);
    }
}

CMesh CModel::ProcessMesh(aiMesh* _mesh,
    const aiScene* _scene){

    // data to fill
    std::vector<Vertex> vertices;

    std::vector<unsigned int> indices;

    std::vector<Texture> textures;

    // walk through each of the _mesh's vertices
    for (unsigned int i = 0; i < _mesh->mNumVertices; i++){

        Vertex vertex;

        /// we declare a placeholder std::vector since assimp uses its own std::vector
        ///  class that doesn't directly convert to glm's vec3 class so we transfer 
        /// the data to this placeholder glm::vec3 first.
        glm::vec3 vector; 

        // positions
        vector.x = _mesh->mVertices[i].x;
        vector.y = _mesh->mVertices[i].y;
        vector.z = _mesh->mVertices[i].z;

        vertex.Position = vector;

        // normals
        if (_mesh->HasNormals()){

            vector.x = _mesh->mNormals[i].x;
            vector.y = _mesh->mNormals[i].y;
            vector.z = _mesh->mNormals[i].z;

            vertex.Normal = vector;
        }
        // texture coordinates
        if (_mesh->mTextureCoords[0]){

            glm::vec2 vec;

            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = _mesh->mTextureCoords[0][i].x;
            vec.y = _mesh->mTextureCoords[0][i].y;

            vertex.TexCoords = vec;

            // tangent
            vector.x = _mesh->mTangents[i].x;
            vector.y = _mesh->mTangents[i].y;
            vector.z = _mesh->mTangents[i].z;

            vertex.Tangent = vector;

            // bitangent
            vector.x = _mesh->mBitangents[i].x;
            vector.y = _mesh->mBitangents[i].y;
            vector.z = _mesh->mBitangents[i].z;

            vertex.Bitangent = vector;
        }
        else {

            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    /// now wak through each of the _mesh's faces (a face is a _mesh its triangle) 
    /// and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < _mesh->mNumFaces; i++){

        aiFace face = _mesh->mFaces[i];

        // retrieve all indices of the face and store them in the indices std::vector
        for (unsigned int j = 0; j < face.mNumIndices; j++) {

            indices.push_back(face.mIndices[j]);
        }
    }

    // process materials
    aiMaterial* material = _scene->mMaterials[_mesh->mMaterialIndex];

    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN

    // 1. diffuse maps
    std::vector<Texture> diffuseMaps = LoadMaterialTextures(material,
        aiTextureType_DIFFUSE, "texture_diffuse");

    textures.insert(textures.end(), 
        diffuseMaps.begin(), 
        diffuseMaps.end());

    // 2. specular maps
    std::vector<Texture> specularMaps = LoadMaterialTextures(material, 
        aiTextureType_SPECULAR, "texture_specular");

    textures.insert(textures.end(), 
        specularMaps.begin(), 
        specularMaps.end());

    // 3. normal maps
    std::vector<Texture> normalMaps = LoadMaterialTextures(material, 
        aiTextureType_HEIGHT, "texture_normal");

    textures.insert(textures.end(), 
        normalMaps.begin(), 
        normalMaps.end());

    // 4. height maps
    std::vector<Texture> heightMaps = LoadMaterialTextures(material, 
        aiTextureType_AMBIENT, "texture_height");

    textures.insert(textures.end(), 
        heightMaps.begin(), 
        heightMaps.end());

    // return a _mesh object created from the extracted mesh data
    //return CMesh(vertices, indices, textures);
}

std::vector<Texture> CModel::LoadMaterialTextures(aiMaterial* _mat, 
    aiTextureType _type, std::string _typeName){

   //std::std::vector<Texture> textures;
   //
   //for (unsigned int i = 0; i < _mat->GetTextureCount(_type); i++){
   //
   //    aiString str;
   //
   //    _mat->GetTexture(_type, i, &str);
   //    bool skip = false;
   //
   //    for (unsigned int j = 0; j < m_textures_loaded.size(); j++){
    //
    //        if (std::strcmp(m_textures_loaded[j].path.data(), str.C_Str()) == 0){
    //
    //            textures.push_back(m_textures_loaded[j]);
    //            skip = true;
    //            break;
    //        }
    //    }
   //
   //    if (!skip){
   //
   //        CGraphicApi object;
   //
   //        // if texture hasn't been loaded already, load it
   //        Texture texture;
   //        texture.id = object.LoadTextureFromFile(str.C_Str(), m_directory);
   //        texture.type = _typeName;
   //        texture.path = str.C_Str();
   //        textures.push_back(texture);
   //
   //        // add to loaded textures
   //        m_textures_loaded.push_back(texture); 
   //    }
   //}
   //return textures;
}

void CModel::Init(char* _path){

    LoadModel(_path);
}

//void CModel::Draw(){
//
//    
//}

*/