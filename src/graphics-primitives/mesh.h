#pragma once

#include <vector>
#include <memory>
#include "vertex.h"

/***
 * 
 * Holds vertex data associated with a graphical structure.
 * That data is put into buffers.
 * 
 ***/


class Shader;


class Mesh {
private:
    unsigned int m_vao, m_vbo, m_ebo;
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
    GlDraw mDrawType;

    
    void GenMesh();
    void IndexDraw();
    void ArrayDraw();
    


public:

    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, GlDraw type);
    ~Mesh();    
    void Bind();
    void UnBind();
    void Draw(const std::shared_ptr<Shader>& shader);

    

};