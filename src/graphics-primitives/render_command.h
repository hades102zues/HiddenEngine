#pragma once
#include <memory>

/**
 * Houses issued graphics api calls. 
 * The Command will be Executed by the renderer.
*/
class RenderCommand{
public:
    virtual void Execute() = 0;
    virtual ~RenderCommand() = default;
};



class Mesh;
class Shader;
class RenderMesh : public RenderCommand {

private: 
    // Weak pointers don't assume ownership
    // Great for data that has chance of not existing  
    std::weak_ptr<Mesh>  mMesh;
    std::weak_ptr<Shader> mShader;
public:
    RenderMesh(std::weak_ptr<Mesh> mesh, std::weak_ptr<Shader> shader);
    ~RenderMesh();
    virtual void Execute();
};