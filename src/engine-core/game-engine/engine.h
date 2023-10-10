#pragma once

#include <SDL2/SDL.h> 
#include "../window/window.h"
#include "../renderer/renderer.h"
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
        bool mIsRunning;
        std::unique_ptr<SDLWindow> mEngineWindow;
        std::unique_ptr<Renderer> mEngineRenderer;

        void Render();
        void HandleInput();
        void Update();

        // TODO: WRITE THE SINGLETON BEHAVIOUR

};