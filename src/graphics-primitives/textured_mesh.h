#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include "texture.h"
#include "vertex.h"


/***
 * 
 * Holds vertex data associated with a graphical structure.
 * This vertex data is put into buffers.
 * Also holds pointers to textures.
 * 
 ***/




class Shader;

class TexturedMesh {
private:
    unsigned int m_vao, m_vbo, m_ebo;
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
    std::vector<std::weak_ptr<Texture>> mMapRefs;
    GlDraw mDrawType;

    
    void GenMesh();
    void IndexDraw();
    void ArrayDraw();
    void BindTextures(const std::shared_ptr<Shader>& shader);

public:

    TexturedMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, std::vector<std::weak_ptr<Texture>> mapRefs,  GlDraw type);
    ~TexturedMesh();    
    void Bind();
    void UnBind();
    void Draw(const std::shared_ptr<Shader>& shader);

    

};