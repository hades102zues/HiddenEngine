#include "engine.h"
#include "../logger/logger.h"
#include <iostream>


#include "../../common/path_dict.h"
#include "../../common/read_file.h"


#include "../../graphics-primitives/textured_mesh.h"
#include "../../graphics-primitives/shader.h"
#include "../../graphics-primitives/texture.h"
#include "../../graphics-primitives/render_command.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../graphics-primitives/model_loader.h"
#include "../../graphics-primitives/terrain.h"


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

    
// ******
// **** TEST CODE


std::string vertexSrc = readFile(pathLibrary.ShaderRoot + "texture_shader.vs");
std::string fragmentSrc = readFile(pathLibrary.ShaderRoot + "texture_shader.fs");
std::shared_ptr<Shader> shader = std::make_shared<Shader>(vertexSrc, fragmentSrc);




std::string modelDirectory = "3d_models/backpack/";
modelDirectory = pathLibrary.AssetRoot+ modelDirectory;
Model loader;
loader.LoadModel("backpack.obj", modelDirectory);


// ******
// ****


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


// ******
// **** TEST CODE

glm::mat4 model = glm::mat4(1.0f);
glm::mat4 view = glm::mat4(1.0f);
glm::mat4 projection = glm::mat4(1.0f);



model = glm::rotate(model, (float)(SDL_GetTicks() / 1000.f) * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
view =  glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));


float fov = 45; //degrees
float aspectRatio = (float)mEngineWindow->GetWidth() / (float)mEngineWindow->GetHeight(); 
float distanceToNearPlane = 0.1f;
float distanceToFarPlane = 100.0f;
projection = glm::perspective(glm::radians(fov), aspectRatio, distanceToNearPlane, distanceToFarPlane);


shader->Bind();
    shader->SetMat4(model, "model");
    shader->SetMat4(view, "view");
    shader->SetMat4(projection, "projection");
shader->UnBind();


// this should be a function in the model?
//auto meshes = loader.GetMeshes();
for ( auto mesh : loader.GetMeshes()) {
    auto renderCommand = std::make_unique<RenderTexturedMesh>(mesh, shader);
    mEngineRenderer->Submit(std::move(renderCommand));
}

Terrain terrain(0.0f, 0.0f, 3.0f, 3);
// ******
// ****



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