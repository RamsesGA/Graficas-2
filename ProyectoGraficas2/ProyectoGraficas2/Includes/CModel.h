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
       
        /// <summary>
        /// Miembro para almacenar el nombre
        /// completo de la carpeta
        /// </summary>
        std::string m_directory;
        /// <summary>
        /// Miembro para almacenar una cadena de
        /// samplers
        /// </summary>
        std::vector <CSamplerState*> m_sampler;
        /// <summary>
        /// Miembro para almacenar una cadena de Meshes
        /// </summary>
        std::vector<CMesh*> m_meshes;
        /// <summary>
        /// Miembro para almacenar una cadena de texturas
        /// </summary>
        std::vector<Texture> m_textures;

    public:
        ///
        /// Métodos
        /// 

        ///Constructor
        CModel() = default;
        ///Destructor
        ~CModel() = default;

        /// <summary>
        /// Función para inicializar los miembros
        /// de la clase e iniciar con assimp
        /// </summary>
        void Init(std::string const& _path,
            CGraphicApi* _graphicApi);
        /// <summary>
        /// Función para dibujar en base a
        /// m_meshes
        /// </summary>
        void Draw(CGraphicApi* _graphicApi);
        /// <summary>
        /// Función para procesar la información
        /// de los nodos
        /// </summary>
        void ProcessNode(aiNode* _node,
            const aiScene* _scene,
            CGraphicApi* _graphicApi);
        /// <summary>
        /// Función para procesar la información
        /// de los meshes
        /// </summary>
        CMesh* ProcessMesh(aiMesh* _mesh,
            const aiScene* _scene,
            CGraphicApi* _graphicApi);
        /// <summary>
        /// Función para la carga de la textura del modelo
        /// </summary>
        std::vector<Texture> LoadMaterialTextures(aiMaterial* _mat,
            aiTextureType _type,
            CGraphicApi* _graphicApi);
        /// <summary>
        /// Función para obtener la dirección de la textura
        /// </summary>
        std::string GetTexturePath(std::string _file);
};