#include "engine.h"
#include "../logger/logger.h"
#include <iostream>


#include "../../graphics-primitives/mesh.h"
#include "../../graphics-primitives/shader.h"
#include "../../graphics-primitives/render_command.h"

// std::unique_ptr<HiddenEngine> HiddenEngine::sEngineInstance;
// std::unique_ptr<HiddenEngine>& HiddenEngine::GetEngine() {

//     // if an instance exists then return it
//     if (sEngineInstance) {
//         return sEngineInstance;
//     }

//     // create and instance
//     sEngineInstance = std::make_unique<HiddenEngine>();
//     return sEngineInstance;
// }


HiddenEngine::HiddenEngine() {
    mIsRunning = false;

}

int HiddenEngine::Initialize() {

    

    // *************
    // **** Initialize Logger
    Logger::Init();
    HIDDEN_INFO("Initializing Engine...");

    // *************
    // **** Initialize SDL Window
    mEngineWindow = std::make_unique<SDLWindow>();
    if(!mEngineWindow->Init()) {
        Shutdown();
        return 0;
    }

    // *************
    // **** Initialize Renderer
    mEngineRenderer = std::make_unique<Renderer>();
    mEngineRenderer->Init();


    // *************
    // **** Closeout

    mIsRunning = true;
    HIDDEN_INFO("Initialized Engine");
    return 1;
    

}

void HiddenEngine::Run() {

struct Vertex vert1 = {glm::vec3(-0.5f, 0.0f, 0.0f)};
struct Vertex vert2 = {glm::vec3(0.5f, 0.0f, 0.0f)};
struct Vertex vert3 = {glm::vec3(0.0f, 0.5f, 0.0f)};

std::vector<Vertex> vertices{vert1, vert2, vert3};
std::vector<unsigned int> indices{0,1,2};
std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(vertices, indices);


std::string vertexSrc = R"(
    #version 330 core
    layout(location = 0) in vec3 aPosition;

    out vec3 v_Position;

    void main() {
        v_Position = aPosition;
        gl_Position = vec4(aPosition, 1.0);

    }
)";

std::string fragmentSrc = R"(
    #version 330 core
    in vec3 v_Position;
    out vec4 f_Color;

    void main() {
        f_Color = vec4(v_Position, 1.0);
    }

)";

std::shared_ptr<Shader> shader = std::make_shared<Shader>(vertexSrc, fragmentSrc);



    HIDDEN_INFO("Engine is running");
    while (mIsRunning) {
        HandleInput();
        Update();

        auto renderCommand = std::make_unique<RenderMesh>(mesh, shader);
        mEngineRenderer->Submit(std::move(renderCommand));
        Render();
  
    }
}

void HiddenEngine::HandleInput() {
    // i don't like the setup of this function
    mEngineWindow->HandleInputs(mIsRunning);
}

void HiddenEngine::Update() {

}

void HiddenEngine::Render() {

// Clear Window
mEngineRenderer->GlClear();

// Issue draw calls
mEngineRenderer->Flush();
// Swap buffers
mEngineWindow->SwapBuffers();

}



void HiddenEngine::GetInfo() {
#ifdef HIDDEN_CONFIG_DEBUG
    HIDDEN_INFO("Configuration : DEBUG" );
#endif
#ifdef HIDDEN_CONFIG_RELEASE
    HIDDEN_INFO("Configuration : RELEASE" );
#endif
#ifdef HIDDEN_PLATFORM_MAC
    HIDDEN_INFO("Platform : MACOSX");
#endif
#ifdef HIDDEN_PLATFORM_WINDOWS
     HIDDEN_INFO("Platform : WINDOWS");
#endif
}

void HiddenEngine::Shutdown() {
    HIDDEN_INFO("Engine shutting down....");

    mEngineWindow->Shutdown();
    Logger::Shutdown();
}

HiddenEngine::~HiddenEngine() {};