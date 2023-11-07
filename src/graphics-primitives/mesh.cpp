#include "mesh.h"
#include <glad/glad.h>

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, GlDraw type) {
    m_vertices = vertices;
    m_indices = indices;
    mDrawType = type;
    GenMesh();

}


void Mesh::GenMesh() {

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);


    glBindVertexArray(m_vao);

    
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

    // vertex position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // texture coordinates
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TextCoords));


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
        IndexDraw();
    }

    if (mDrawType == GlDraw::MESH_ARRAY_DRAW) {
        ArrayDraw();
    }
}
Mesh::~Mesh() {
    glDeleteBuffers(1, &m_ebo);
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
}


