#include "engine.h"
#include "../logger/logger.h"
#include <iostream>

HiddenEngine::HiddenEngine() {
    mIsRunning = false;
}

int HiddenEngine::Initialize() {


    // *************
    // **** Initialize Logger
    Logger::Init();


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
    HIDDEN_INFO("Engine Initialization Completed");
    return 1;
    

}

void HiddenEngine::Run() {

    HIDDEN_INFO("Engine is running");
    while (mIsRunning) {
        HandleInput();
        Update();
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
    mEngineWindow->GlClear();

    
    mEngineWindow->Render();
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