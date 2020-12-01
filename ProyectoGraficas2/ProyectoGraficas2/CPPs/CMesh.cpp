#include "..\Includes\CMesh.h"

/*

    void CMesh::SetUpMesh(){
    
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);
    
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    
        glBufferData(GL_ARRAY_BUFFER, 
            m_vertices.size() * sizeof(Vertex), 
            &m_vertices[0], GL_STATIC_DRAW);
    
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 
            m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
            m_indices.size() * sizeof(unsigned int),
            &m_indices[0], GL_STATIC_DRAW);
    
        // vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        // vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    
        glBindVertexArray(0);
    }
    
    void CMesh::Init(std::vector<Vertex> _vertices, 
    	std::vector<unsigned int> _indices, 
    	std::vector<Texture> _textures){
    
    	this->m_vertices = _vertices;
    	this->m_indices = _indices;
    	this->m_textures = _textures;
    
    	SetUpMesh();
    }
    
    void CMesh::Draw(Shader& _shader){
    
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
    
        for (unsigned int i = 0; i < m_textures.size(); i++){
    
            // activate proper texture unit before binding
            glActiveTexture(GL_TEXTURE0 + i); 
    
            // retrieve texture number (the N in diffuse_textureN)
            std::string number;
            std::string name = m_textures[i].type;
    
            if (name == "texture_diffuse") {
    
                number = std::to_string(diffuseNr++);
            }
            else if (name == "texture_specular") {
    
                number = std::to_string(specularNr++);
            }
    
            _shader.setFloat(("material." + name + number).c_str(), i);
    
            glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
        }
    
        glActiveTexture(GL_TEXTURE0);
    
        // draw mesh
        glBindVertexArray(m_VAO);
    
        glDrawElements(GL_TRIANGLES, 
            m_indices.size(), 
            GL_UNSIGNED_INT, 0);
    
        glBindVertexArray(0);
    }

*/