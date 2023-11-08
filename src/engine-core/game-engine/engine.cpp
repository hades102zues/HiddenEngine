#include "engine.h"
#include "../logger/logger.h"
#include <iostream>


#include "../../graphics-primitives/mesh.h"
#include "../../graphics-primitives/shader.h"
#include "../../graphics-primitives/texture.h"
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

std::vector<Vertex> vertices{
        Vertex {glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec2(0.0f, 0.0f)},
        Vertex {glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec2(1.0f, 0.0f)},
        Vertex {glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec2(1.0f, 1.0f)},
        Vertex {glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec2(1.0f, 1.0f)},
        Vertex {glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec2(0.0f, 1.0f)},
        Vertex {glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec2(0.0f, 0.0f)},

        Vertex {glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec2(0.0f, 0.0f)},
        Vertex {glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec2(1.0f, 0.0f)},
        Vertex {glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 1.0f)},
        Vertex {glm::vec3(0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 1.0f)},
        Vertex {glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec2(0.0f, 1.0f)},
        Vertex {glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec2(0.0f, 0.0f)},

        Vertex {glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 0.0f)},
        Vertex {glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec2(1.0f, 1.0f)},
        Vertex {glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec2(0.0f, 1.0f)},
        Vertex {glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec2(0.0f, 1.0f)},
        Vertex {glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec2(0.0f, 0.0f)},
        Vertex {glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 0.0f)},

        Vertex {glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 0.0f)},
        Vertex {glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec2(1.0f, 1.0f)},
        Vertex {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)},
        Vertex {glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec2(0.0f, 1.0f)},
        Vertex {glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec2(0.0f, 0.0f)},
        Vertex {glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 0.0f)},

        Vertex {glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec2(0.0f, 1.0f)},
        Vertex {glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec2(1.0f, 1.0f)},
        Vertex {glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec2(1.0f, 0.0f)},
        Vertex {glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec2(1.0f, 0.0f)},
        Vertex {glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec2(0.0f, 0.0f)},
        Vertex {glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec2(0.0f, 1.0f)},

        Vertex {glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f)},
        Vertex {glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec2(1.0f, 1.0f)},
        Vertex {glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 0.0f)},
        Vertex {glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 0.0f)},
        Vertex {glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec2(0.0f, 0.0f)},
        Vertex {glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec2(0.0f, 1.0f)}
};


// Every vertex attribute is parsed to some location on a VAO
// But each location in the VAO is an array that is populated upon ingestion.
// For example, all the data associated with the very first vertex ingested would be found at index 0 of every location array.
// The API allows us to specifically target indices so that we can reuse vertex data.
std::vector<unsigned int> indices{
                             0, 1, 3,      // vertices of the first triangle
                             1, 2, 3       // vertices of the second triangle
                            };
std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(vertices, indices, GlDraw::MESH_ARRAY_DRAW);






std::string vertexSrc = R"(
    #version 410 core

    layout(location = 0) in vec3 aPosition;
    layout(location = 1) in vec2 aTextureCoords;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    out vec3 v_Position;
    out vec2 v_UVs;
    

    void main() {
        v_Position = aPosition;
        v_UVs = aTextureCoords;
        gl_Position = vec4(aPosition, 1.0);

    }
)";

std::string fragmentSrc = R"(
    #version 410 core

    in vec3 v_Position;
    in vec2 v_UVs;
    uniform sampler2D textureSampler;

    out vec4 f_Color;

    void main() {
        f_Color = texture(textureSampler, v_UVs);
    }

)";
std::shared_ptr<Shader> shader = std::make_shared<Shader>(vertexSrc, fragmentSrc);






std::shared_ptr<Texture> text1 = std::make_shared<Texture>("container", "assets/textures/container.jpg");

   
    int fpsCap = 60;
    float timePerFrame = 1000.0f / fpsCap; // in milliseconds
    float currentTime = SDL_GetTicks(); // in miliseonds
    float prevTime = currentTime; // in miliseconds
    float timeElapsed; // in miliseconds
    float dt; // in seconds


    HIDDEN_INFO("Engine is running");
    while (mIsRunning) {

        // Input Process
        HandleInput();

        // Update game state
        Update();

        auto renderCommand = std::make_unique<RenderTexturedMesh>(mesh, text1, shader);
        mEngineRenderer->Submit(std::move(renderCommand));

        // Render to Screen
        Render();

        // Compute dt & waiting
        currentTime = SDL_GetTicks();
        timeElapsed = currentTime - prevTime;
        dt = timeElapsed / 1000.f;
        prevTime = currentTime;

        if (timeElapsed < timePerFrame) {
            SDL_Delay(timePerFrame - timeElapsed);
        }
  
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
    mEngineWindow->GlClear();

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