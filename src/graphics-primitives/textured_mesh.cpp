#include "textured_mesh.h"
#include <glad/glad.h>
#include "shader.h"
#include "../engine-core/logger/logger.h"


TexturedMesh::TexturedMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, std::vector<std::weak_ptr<Texture>> mapRefs,  GlDraw type) {
    m_vertices = vertices;
    m_indices = indices;
    mDrawType = type;
    mMapRefs = mapRefs;
    GenMesh();
}


void TexturedMesh::GenMesh() {

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
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normals));




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

void TexturedMesh::Bind() {

    glBindVertexArray(m_vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

}

void TexturedMesh::UnBind() {
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

void TexturedMesh::IndexDraw() {
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(m_indices.size()), GL_UNSIGNED_INT, 0);
}

void TexturedMesh::ArrayDraw() {
    glDrawArrays(GL_TRIANGLES, 0, static_cast<unsigned int>(m_vertices.size()));
}

void TexturedMesh::Draw(const std::shared_ptr<Shader>& shader) {

    // bind texture BindTextures
    BindTextures(shader);

    if (mDrawType == GlDraw::MESH_INDEX_DRAW) {
       IndexDraw();
    }

    if (mDrawType == GlDraw::MESH_ARRAY_DRAW) {
        ArrayDraw();
    }

    // Unbind: will just let things get overwritten
}

void TexturedMesh::BindTextures(const std::shared_ptr<Shader>& shader) {
    if (mMapRefs.empty()) {
        return;
    }

    int diffuseSamplerIndex = 0;
    int specularSamplerIndex = 0;
    int gpUnitIndex = 0;

    for (int i = 0; i < mMapRefs.size(); i++) {
       
        // Given that there is no logic in the fragment shaders to loop through all of the map types this could present a problem with the current test setup. 

        // Determine if texture is referable
        auto textureRef = mMapRefs[i].lock();
        if (!textureRef) {
            continue;
        }

        // Set the texture to next available gpu unit
        textureRef->Bind(gpUnitIndex);
        

        // Seperate sampler arrays are created for referencing diffuse and specular textures.
        // A location in those array will hold the gpu unit that the texture is being bound to

        if (textureRef->GetTextureType() == MapType::DIFFUSE) {
            std::string samplerArrayName = "uv_DiffuseSamplers["+std::to_string(diffuseSamplerIndex)+"]"; 
            shader->Set1Int(gpUnitIndex, samplerArrayName);
            gpUnitIndex++;  
            diffuseSamplerIndex++;
        }

        // if (textureRef->GetTextureType() == MapType::SPECULAR) {
        //     std::string samplerArrayName = "uv_SpecularSamplers["+std::to_string(specularSamplerIndex)+"]";
        //     shader->Set1Int(gpUnitIndex, samplerArrayName);
        //     gpUnitIndex++;  
        //     specularSamplerIndex++;
        // }

        
    }

}
TexturedMesh::~TexturedMesh() {
    glDeleteBuffers(1, &m_ebo);
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
}


