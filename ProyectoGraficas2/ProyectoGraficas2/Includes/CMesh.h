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
        /// Miembro para almacenar la
        /// información del vértice
        /// </summary>
        CVertexBuffer* m_vertexBuffer;
        /// <summary>
        /// Miembro para almacenar la
        /// información del índice
        /// </summary>
        CIndexBuffer* m_indexBuffer;
        /// <summary>
        /// Miembro para almacenar la
        /// información de los vértices
        /// </summary>
        std::vector<Vertex>* m_vertices;
        /// <summary>
        /// Miembro para almacenar la
        /// información de los índices
        /// </summary>
        std::vector<unsigned int>* m_indices;
        /// <summary>
        /// Miembro para almacenar la
        /// información de las texturas
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
        /// Función para inicializar los miembros
        /// de la clase
        /// </summary>
        void Init(std::vector<Vertex>* _vertices,
            std::vector<unsigned int>* _indices,
            std::vector<Texture> _textures,
            CGraphicApi* _graphicApi);
        /// <summary>
        /// Función para guardar la información para
        /// m_vertexBuffer y m_indexBuffer
        /// </summary>
        void SetUpMesh(CGraphicApi* _graphicApi);
        /// <summary>
        /// Función para guardar los vértices e índices
        /// y finalmente dibujar
        /// </summary>
        void Draw(CGraphicApi* _graphicApi,
            std::vector <CSamplerState*> _samplerState);
};