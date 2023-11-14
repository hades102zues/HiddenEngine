#pragma once
#include <glm/glm.hpp>
#include <vector>

/***
 * 
 * Holds vertex data associated with a graphical structure.
 * And the buffers they are associated with
 * 
 ***/

enum class GlDraw {
    MESH_INDEX_DRAW = 0,
    MESH_ARRAY_DRAW
};

struct Vertex {
    glm::vec3 Position;
    glm::vec2 TextCoords;
    glm::vec3 Normal;
    
};


class Mesh {
private:
    unsigned int m_vao, m_vbo, m_ebo;
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
    std::vector<unsigned int> mMapRefIds;
    GlDraw mDrawType;

    
    void GenMesh();
    void IndexDraw();
    void ArrayDraw();
    void BindTextures();

public:

    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, GlDraw type);
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<unsigned int>& mapRefIds,  GlDraw type);
    ~Mesh();    
    void Bind();
    void UnBind();
    void Draw();

    

};