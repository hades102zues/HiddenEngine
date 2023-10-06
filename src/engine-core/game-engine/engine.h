#pragma once

#include <SDL2/SDL.h> 
#include "../window/window.h"
#include <memory>




class HiddenEngine {
    public:
        HiddenEngine();
        ~HiddenEngine();
        void GetInfo();
        int Initialize();
        void Run();
        void Shutdown();
    private:
        bool m_isRunning;
        std::shared_ptr<SDLWindow> m_engineWindow;

        void Render();
        void HandleInput();
        void Update();

};