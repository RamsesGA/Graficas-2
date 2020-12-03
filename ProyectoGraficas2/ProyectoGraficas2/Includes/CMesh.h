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
        /// informaci�n del v�rtice
        /// </summary>
        CVertexBuffer* m_vertexBuffer;
        /// <summary>
        /// Miembro para almacenar la
        /// informaci�n del �ndice
        /// </summary>
        CIndexBuffer* m_indexBuffer;
        /// <summary>
        /// Miembro para almacenar la
        /// informaci�n de los v�rtices
        /// </summary>
        std::vector<Vertex>* m_vertices;
        /// <summary>
        /// Miembro para almacenar la
        /// informaci�n de los �ndices
        /// </summary>
        std::vector<unsigned int>* m_indices;
        /// <summary>
        /// Miembro para almacenar la
        /// informaci�n de las texturas
        /// </summary>
        std::vector<Texture> m_textures;

    public:
        ///
        /// M�todos
        /// 
    
        ///Constructor
        CMesh() = default;
        ///Destructor
        ~CMesh() = default;

        /// <summary>
        /// Funci�n para inicializar los miembros
        /// de la clase
        /// </summary>
        void Init(std::vector<Vertex>* _vertices,
            std::vector<unsigned int>* _indices,
            std::vector<Texture> _textures,
            CGraphicApi* _graphicApi);
        /// <summary>
        /// Funci�n para guardar la informaci�n para
        /// m_vertexBuffer y m_indexBuffer
        /// </summary>
        void SetUpMesh(CGraphicApi* _graphicApi);
        /// <summary>
        /// Funci�n para guardar los v�rtices e �ndices
        /// y finalmente dibujar
        /// </summary>
        void Draw(CGraphicApi* _graphicApi,
            std::vector <CSamplerState*> _samplerState);
};