#include <glad/glad.h>
#include "renderer.h"
#include "../logger/logger.h"


Renderer::Renderer() {
    SetGlClear(0.2f, 0.3f, 0.3f, 1.0f); 
}
Renderer::Renderer(float r, float g, float b, float a) {
    SetGlClear(r, g, b, a);
}

void Renderer::Init() {

    HIDDEN_INFO("Initializing Renderer..");

    // *************
    // **** Drawing Attributes
    
    // Set method for depth testing of vertices/fragments
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // If there's transparency(Alpha) then render accordingly
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    HIDDEN_INFO("Initialized Renderer");
}

void Renderer::Flush() {
    while (mRenderComands.size()) {
        auto comm = std::move(mRenderComands.front()); 
        mRenderComands.pop();
        comm->Execute();
    }
    HIDDEN_ASSERT(mRenderComands.size() == 0, "Flush() did not empty queue");
}

void Renderer::Submit(std::unique_ptr<RenderCommand> command) {
    mRenderComands.push(std::move(command));
    
}

// void SubmitCommands(std::vector<RenderCommand> commands) {

// }

// 
void Renderer::ClearQueue() {
    HIDDEN_ASSERT(mRenderComands.size() == 0, "Unflushed Render Commands in queue");
    while (mRenderComands.size()) {
        mRenderComands.pop();
    }
    
}


void Renderer::Shutdown() {
    ClearQueue();
    GlClear();
}
void Renderer::SetGlClear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}
void Renderer::GlClear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
}

Renderer::~Renderer() {
    Shutdown();
}


