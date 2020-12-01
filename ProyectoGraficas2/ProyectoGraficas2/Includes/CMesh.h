#pragma once
#include <string>
#include <vector>

/*

struct Vertex {

    //glm::vec3 Position;
    //glm::vec3 Normal;
    //glm::vec2 TexCoords;
    //glm::vec3 Tangent;
    //glm::vec3 Bitangent;
};

struct Texture {

    unsigned int id;
    std::string type;
    std::string path;
};


class CMesh {

    private:
        ///
        /// Miembros
        /// 

        /// <summary>
        /// Vertex Array Object
        /// </summary>
        unsigned int m_VAO;
        /// <summary>
        /// Vertex Buffer Object
        /// </summary>
        unsigned int m_VBO;
        /// <summary>
        /// Element Buffer Object
        /// </summary>
        unsigned int m_EBO;
    
        ///
        /// Métodos
        /// 
        
        void SetUpMesh();

    public:
        ///
        /// Miembros
        /// 

        // mesh data
        std::vector<Vertex> m_vertices;

        std::vector<unsigned int> m_indices;

        std::vector<Texture> m_textures;
       
        ///
        /// Métodos
        /// 
    
        ///Constructor
        CMesh() = default;
        ///Destructor
        ~CMesh() = default;

        void Init(std::vector<Vertex> _vertices,
            std::vector<unsigned int> _indices,
            std::vector<Texture> _textures);

        //void Draw(Shader& _shader);
};

*/