#pragma once
#include <queue>
#include "../../graphics-primitives/render_command.h"

class Renderer {
private:
    std::queue< std::unique_ptr<RenderCommand> > mRenderComands;

public:
    Renderer();
    Renderer(float r, float g, float b, float a);
    ~Renderer();
    void Init();
    void Flush();
    void Submit(std::unique_ptr<RenderCommand> command);
    void ClearQueue();
    void SetGlClear(float r, float g, float b, float a);
    void GlClear();
    void Shutdown();
    

    // Carry out the render commands
    
};