#include "engine.h"
#include "../logger/logger.h"
#include <iostream>


#include "../../common/path_dict.h"

#include "../../graphics-primitives/mesh.h"
#include "../../graphics-primitives/shader.h"
#include "../../graphics-primitives/texture.h"
#include "../../graphics-primitives/render_command.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../graphics-primitives/model_loader.h"


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

std::string vertexSrc = R"(
    #version 410 core

    layout(location = 0) in vec3 aPosition;
    layout(location = 1) in vec2 aTextureCoords;
    layout(location = 2) in vec3 aNormal;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;


    out vec2 v_TextureUVs;
    out vec3 v_WorldVertex;
    out vec3 v_WorldNormal;
    

    void main() {
        v_TextureUVs = aTextureCoords;

        v_WorldVertex = vec3(model * vec4(aPosition, 1.0));

        mat3 NormalMatrix = mat3(transpose(inverse(model)));
        v_WorldNormal = vec3(NormalMatrix * aNormal);

        gl_Position = projection * view * model * vec4(aPosition, 1.0);

    }
)";

std::string fragmentSrc = R"(
    #version 410 core

    in vec2 v_TextureUVs;
    in vec3 v_WorldVertex;
    in vec3 v_WorldNormal;


    uniform sampler2D uv_DiffuseSamplers[10];
    uniform sampler2D uv_SpecularSamplers[10];
    out vec4 f_Color;

    void main() {
        //*********************
        // Camera
        vec3 cameraPos = vec3(0.0, 0.0, 0.0);

        //*********************
        // Basic Light Properties

        vec3 lightColor = vec3(1.0, 1.0, 1.0);
        vec3 lightPos = vec3(0.0, 5.0, 1.0);
        float lightAmbientIntensity = 0.1;

        //*********************
        // Ambient Calculations

        // AmbientStrength represents what fraction of the original light is now avaiable in the background. 
        float ambientStrenth = lightAmbientIntensity; 
        vec3 ambient = ambientStrenth * lightColor;


        //*********************
        // Diffuse Calculations

        vec3 norm = normalize(v_WorldNormal);
        vec3 toLight = normalize(lightPos - v_WorldVertex);
        float diff = max(dot(toLight, norm), 0.0);
        vec3 diffuse = diff * lightColor;


        //*********************
        // Specular Calculations

        float reflectivity = 0.5;
        vec3 toEye = normalize(cameraPos - v_WorldVertex);
        vec3 reflectedRay = reflect(-toLight, norm);  
        float disperseFactor = pow(max(dot(toEye, reflectedRay), 0.0), 32);
        vec3 specular = disperseFactor * (reflectivity * lightColor); 


       //*********************
       // Results

        vec3 fragColor = texture(uv_DiffuseSamplers[0], v_TextureUVs).xyz;
        vec3 result = ( ambient + diffuse + specular ) * fragColor;

        f_Color = vec4(result, 1.0); 
    }

)";
std::shared_ptr<Shader> shader = std::make_shared<Shader>(vertexSrc, fragmentSrc);




std::string modelDirectory = "3d_models/backpack/";
modelDirectory = pathLibrary.AssetRoot+ modelDirectory;
ModelLoader loader;
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

auto meshes = loader.GetMeshes();
for ( auto mesh : meshes) {
    auto renderCommand = std::make_unique<RenderMesh>(mesh, shader);
    mEngineRenderer->Submit(std::move(renderCommand));
}


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