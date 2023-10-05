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
        std::cout <<  "Error creating window: " << SDL_GetError() << std::endl;
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
        std::cout << "Error creating SDL window."  << std::endl;
        Shutdown();
        return 0;
    }

    // *************
    // **** Bind OpenGL to SDL Window


    m_isRunning = true;
    return 1;
    

}

void HiddenEngine::Run() {
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
    std::cout << "Configuration : DEBUG " << std::endl;
#endif
#ifdef HIDDEN_CONFIG_RELEASE
    std::cout << "Configuration : RELEASE" << std::endl;
#endif
#ifdef HIDDEN_PLATFORM_MAC
    std::cout << "Platform : MACOSX" << std::endl;
#endif
#ifdef HIDDEN_PLATFORM_WINDOWS
    std::cout << "Platform : WINDOWS" << std::endl;
#endif
}

void HiddenEngine::Shutdown() {

    Logger::Shutdown();

    SDL_Quit();
}
HiddenEngine::~HiddenEngine() {};