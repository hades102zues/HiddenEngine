#include <glad/glad.h>

#include "../engine-core/logger/logger.h"
#include "render_command.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"



// **************************************
// *** BASIC MESH ***

RenderMesh::RenderMesh(std::weak_ptr<Mesh> mesh, std::weak_ptr<Shader> shader)
:mMesh(mesh), mShader(shader) {}


void RenderMesh::Execute() {

    // Must promote weak pointers to shared pointer before they can be used.
    // If a resource doesn't exist-- a nullptr is assigned
    std::shared_ptr<Mesh> mesh = mMesh.lock();
    std::shared_ptr<Shader> shader = mShader.lock();


    if (!(mesh && shader)) {
        HIDDEN_WARN("Attempted to render mesh on absent data");
        return;
    }

    shader->Bind();
    mesh->Bind();
        mesh->IndexDraw();
    mesh->UnBind();
    shader->UnBind();
    


}

RenderMesh::~RenderMesh() {
    //
}


// **************************************
// *** TEXTURED MESH ***

RenderTexturedMesh::RenderTexturedMesh(std::weak_ptr<Mesh> mesh,  std::weak_ptr<Texture> texture, std::weak_ptr<Shader> shader):
mMesh(mesh), mTexure(texture), mShader(shader){}


void RenderTexturedMesh::Execute() {

    // Must promote weak pointers to shared pointer before they can be used.
    // If a resource doesn't exist-- a nullptr is assigned
    std::shared_ptr<Mesh> mesh = mMesh.lock();
    std::shared_ptr<Shader> shader = mShader.lock();
    std::shared_ptr<Texture> texture = mTexure.lock();


    if (!(mesh && shader && texture)) {
        HIDDEN_WARN("Attempted to render textured mesh on absent data");
        return;
    }

    shader->Bind();
    mesh->Bind();
    texture->Bind();
        mesh->IndexDraw();
    texture->UnBind();
    mesh->UnBind();
    shader->UnBind();
    


}


RenderTexturedMesh::~RenderTexturedMesh() {

}

