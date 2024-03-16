#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include "../../graphics-primitives/camera.h"

class SDLWindow {
    private :
        SDL_Window* m_window = nullptr;
        int mWindowHeight;
        int mWindowWidth;
    public :
        
        SDLWindow() = default;
        ~SDLWindow() = default;

        SDL_Window* Get();
        int Init();
        void HandleKeyPress(bool& isRunning,const std::shared_ptr<Camera>& gameCamera, float dt);
        void SwapBuffers();
        void Shutdown();
        void GlClear();
        int GetWidth();
        int GetHeight();

};