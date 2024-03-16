#pragma once

#include <SDL2/SDL.h> 
#include "../window/window.h"
#include "../renderer/renderer.h"
#include "../../graphics-primitives/camera.h"
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
        std::shared_ptr<Camera> mCamera;
        float mDeltaTime = 0.0f; // in seconds


        void Render();
        void HandleInput();
        void Update();



        // TODO: WRITE THE SINGLETON BEHAVIOUR
        // static std::unique_ptr<HiddenEngine> sEngineInstance;
        // static std::unique_ptr<HiddenEngine>& GetEngine();
        


};