#include "window.h"
#include <glad/glad.h>
#include <SDL2/SDL.h> 
#include "../logger/logger.h"

SDL_Window* SDLWindow::Get() {
    return m_window;
}

int SDLWindow::Init() {
    HIDDEN_INFO("Initializing SDL_Window");

    // *************
    // **** Initialize SDL Window

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        HIDDEN_ERROR("Error initializing SDL {}", SDL_GetError());
        SDL_Quit();
        return 0;
    }


    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);

    int windowHeight = 600;
    int windowWidth = 800;
    m_window = SDL_CreateWindow(
                            "Game"
                            , SDL_WINDOWPOS_CENTERED
                            , SDL_WINDOWPOS_CENTERED
                            , windowWidth
                            , windowHeight
                            , SDL_WINDOW_OPENGL
            );

    if (!m_window) {
        HIDDEN_ERROR("Error creating SDL window: {} ", SDL_GetError());
        SDL_Quit();
        return 0;
    }



    // *************
    // **** Bind OpenGL context to SDL Window

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // not allowing deprecated GL functions
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    auto createdGlContext = SDL_GL_CreateContext(m_window);

    if (!createdGlContext) {
        HIDDEN_ERROR("Error create GL Context");
        SDL_Quit();
        return 0;
    }

    if(!gladLoadGLLoader(SDL_GL_GetProcAddress)){
        HIDDEN_ERROR("Glad failed to initialize");
        SDL_Quit();
        return 0;
    }





    // *************
    // **** Closeout
    HIDDEN_INFO("Initialized SDL_Window");
    return 1;
    

}

void SDLWindow::HandleInputs(bool& m_isRunning) {
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

void SDLWindow::GlClear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
}

void SDLWindow::SwapBuffers() {

    SDL_GL_SwapWindow(m_window);
}

void SDLWindow::Shutdown() {
    SDL_Quit();
}