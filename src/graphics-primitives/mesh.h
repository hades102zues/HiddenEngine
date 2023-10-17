#pragma once
#include <glm/glm.hpp>
#include <vector>

/***
 * 
 * Holds vertex data associated with a graphical structure.
 * And the buffers they are associated with
 * 
 ***/


struct Vertex {
    glm::vec3 Position;
    glm::vec2 TextCoords;
    //glm::vec3 Normal;
    
};


class Mesh {
private:
    unsigned int m_vao, m_vbo, m_ebo;
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

    void GenMesh();

public:

    Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
    ~Mesh();    
    void Bind();
    void UnBind();
    void IndexDraw();
    

};