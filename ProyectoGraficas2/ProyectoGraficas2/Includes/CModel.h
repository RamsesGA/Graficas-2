#pragma once
#include "CMesh.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

class CTexture;

class CModel {

    private:
        ///
        /// Miembros
        /// 
       
        std::string m_directory;

        std::vector <CSamplerState*> m_sampler;

        std::vector<CMesh*> m_meshes;

        std::vector<Texture> m_textures;

    public:
        ///
        /// Métodos
        /// 

        ///Constructor
        CModel() = default;
        ///Destructor
        ~CModel() = default;

        void Init(std::string const& _path,
            CGraphicApi* _graphicApi);

        void Draw(CGraphicApi* _graphicApi);

        void ProcessNode(aiNode* _node,
            const aiScene* _scene,
            CGraphicApi* _graphicApi);

        CMesh* ProcessMesh(aiMesh* _mesh,
            const aiScene* _scene,
            CGraphicApi* _graphicApi);

        std::vector<Texture> LoadMaterialTextures(aiMaterial* _mat,
            aiTextureType _type,
            CGraphicApi* _graphicApi);

        std::string GetTexturePath(std::string _file);
};