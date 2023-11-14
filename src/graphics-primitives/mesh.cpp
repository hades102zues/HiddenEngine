#include "mesh.h"
#include <glad/glad.h>

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, GlDraw type) {
    m_vertices = vertices;
    m_indices = indices;
    mDrawType = type;
    GenMesh();

}

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<unsigned int>& mapRefIds,  GlDraw type) {
    m_vertices = vertices;
    m_indices = indices;
    mDrawType = type;
    mMapRefIds = mapRefIds;
    GenMesh();
}


void Mesh::GenMesh() {

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);


    glBindVertexArray(m_vao);

    
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);



    // *************
    // Storing Vertex Properites

    // Each location in the AttribArray will be tasked with holding a particular property of the vertices
    // And at every location will be an array 
    
    // Location 0 will hold vertex position (x,y,z)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // Location 1 will hold texture coordinates (u,v)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TextCoords));

    // Location 2 will hold Normals (x,y,z)




    // *************
    // Storing Indices
    
    // Indices provide a method of reusing our stored vertex data.
    // We mentioned that each location manages a specific vector property, in an array.
    
    // Then per our setup above, for example, we know that
    //      attribArray[0].list[0] position of vertex1
    //      [1][0] texture coordinates of vertex1
    //      [2][0] normal of vertex1

    // Clearly, we can reference vertex1 by refering to a specific index where each of its properties
    // would have been stored.


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);




    glBindVertexArray(0);
}

void Mesh::Bind() {

    glBindVertexArray(m_vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    // glEnableVertexAttribArray(2);

}

void Mesh::UnBind() {
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    // glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

void Mesh::IndexDraw() {
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(m_indices.size()), GL_UNSIGNED_INT, 0);
}

void Mesh::ArrayDraw() {
    glDrawArrays(GL_TRIANGLES, 0, static_cast<unsigned int>(m_vertices.size()));
}

void Mesh::Draw() {
    if (mDrawType == GlDraw::MESH_INDEX_DRAW) {
        
        // bind texture handles
        IndexDraw();
    }

    if (mDrawType == GlDraw::MESH_ARRAY_DRAW) {
        // bind texture handles
        ArrayDraw();
    }
}

void Mesh::BindTextures() {
    if (!mMapRefIds.size()) {
        return;
    }

    // set the uniforms
}
Mesh::~Mesh() {
    glDeleteBuffers(1, &m_ebo);
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
}


