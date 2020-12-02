#pragma once
#include "Structures.h"

#include <string>
#include <vector>

class CGraphicApi;
class CVertexBuffer;
class CIndexBuffer;
class CSamplerState;

class CMesh {

    private:
        ///
        /// Miembros
        /// 

        /// <summary>
        /// 
        /// </summary>
        CVertexBuffer* m_vertexBuffer;
        /// <summary>
        /// 
        /// </summary>
        CIndexBuffer* m_indexBuffer;
        /// <summary>
        /// 
        /// </summary>
        std::vector<Vertex>* m_vertices;
        /// <summary>
        /// 
        /// </summary>
        std::vector<unsigned int>* m_indices;
        /// <summary>
        /// 
        /// </summary>
        std::vector<Texture> m_textures;

    public:
        ///
        /// Métodos
        /// 
    
        ///Constructor
        CMesh() = default;
        ///Destructor
        ~CMesh() = default;

        /// <summary>
        /// 
        /// </summary>
        void Init(std::vector<Vertex>* _vertices,
            std::vector<unsigned int>* _indices,
            std::vector<Texture> _textures,
            CGraphicApi* _graphicApi);
        /// <summary>
        /// 
        /// </summary>
        void SetUpMesh(CGraphicApi* _graphicApi);
        /// <summary>
        /// 
        /// </summary>
        void Draw(CGraphicApi* _graphicApi,
            std::vector <CSamplerState*> _samplerState);
};