#pragma once
#include <glad/glad.h>
#include <SDL2/SDL.h> 





class HiddenEngine {
    public:
        HiddenEngine();
        ~HiddenEngine();
        void GetInfo();
        int Initialize();
        void Run();
        void Shutdown();
    private:
        int m_windowHeight;
        int m_windowWidth;
        SDL_Window* m_window;
        bool m_isRunning;

        void HandleInput();
        void Update();
        void Render();
};