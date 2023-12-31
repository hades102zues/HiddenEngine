#pragma once
#include <SDL2/SDL.h>

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
        void HandleInputs(bool& isRunning);
        void SwapBuffers();
        void Shutdown();
        void GlClear();
        int GetWidth();
        int GetHeight();

};