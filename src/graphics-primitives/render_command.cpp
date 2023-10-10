#include <glad/glad.h>

#include "../engine-core/logger/logger.h"
#include "render_command.h"
#include "shader.h"
#include "mesh.h"


RenderMesh::RenderMesh(std::weak_ptr<Mesh> mesh, std::weak_ptr<Shader> shader)
:mMesh(mesh), mShader(shader) {}


void RenderMesh::Execute() {

    // Must promote weak pointers to shared pointer before they can be used.
    // If a resource doesn't exist-- a nullptr is assigned
    std::shared_ptr<Mesh> mesh = mMesh.lock();
    std::shared_ptr<Shader> shader = mShader.lock();


    if (!(mesh && shader)) {
        HIDDEN_WARN("Attempted to issue render mesh on absent data");
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


