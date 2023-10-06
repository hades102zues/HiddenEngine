#include "engine.h"
#include "../logger/logger.h"
#include <iostream>

HiddenEngine::HiddenEngine() {
    m_isRunning = false;
}

int HiddenEngine::Initialize() {


    // *************
    // **** Initialize Logger
    Logger::Init();


    // *************
    // **** Initialize SDL Window
    m_engineWindow = std::make_shared<SDLWindow>();
    if(!m_engineWindow->Init()) {
        Shutdown();
        return 0;
    }


    // *************
    // **** Closeout

    m_isRunning = true;
    HIDDEN_INFO("Engine Initialization Completed");
    return 1;
    

}

void HiddenEngine::Run() {

    HIDDEN_INFO("Engine is running");
    while (m_isRunning) {
        HandleInput();
        Update();
        Render();
  
    }
}

void HiddenEngine::HandleInput() {
    // i don't like the setup of this function
    m_engineWindow->HandleInputs(m_isRunning);
}

void HiddenEngine::Update() {

}

void HiddenEngine::Render() {
    m_engineWindow->Clear();
    m_engineWindow->Render();
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

    Logger::Shutdown();

    SDL_Quit();
}
HiddenEngine::~HiddenEngine() {};