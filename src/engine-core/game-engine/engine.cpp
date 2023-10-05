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
    // **** Initialize SDL2

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        HIDDEN_ERROR("Error initializing SDL {}", SDL_GetError());
        Shutdown();
        return 0;
    }


    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);

    m_windowHeight = 600;
    m_windowWidth = 800;
    m_window = SDL_CreateWindow(
                            "Game"
                            , SDL_WINDOWPOS_CENTERED
                            , SDL_WINDOWPOS_CENTERED
                            , m_windowWidth
                            , m_windowHeight
                            , 0
            );
    if (!m_window) {
        HIDDEN_ERROR("Error creating SDL window");
        Shutdown();
        return 0;
    }

    // *************
    // **** Bind OpenGL to SDL Window


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
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT: // usr pressed X on window
                m_isRunning = false;
                break;
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    m_isRunning = false;
                }
                break;
        }
    }
}
void HiddenEngine::Update() {

}
void HiddenEngine::Render() {

}
void HiddenEngine::GetInfo() {
#ifdef HIDDEN_CONFIG_DEBUG
    HIDDEN_INFO("Configuration : DEBUG" );
#endif
#ifdef HIDDEN_CONFIG_RELEASE
    HIDDEN_INFO("Configuration : Release" );
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