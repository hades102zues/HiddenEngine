#pragma once
#include <memory>

/**
 * Houses issued graphics api calls. 
 * The Command will be Executed by the renderer.
*/


class RenderCommand {
public:
    virtual void Execute() = 0;
    virtual ~RenderCommand() {}
};

class Mesh;
class Shader;
class Texture;





// **************************************
// *** BASIC MESH ***

class RenderMesh : public RenderCommand {

private: 
    // Weak pointers don't assume ownership
    // Great for data that has chance of not existing  
    std::weak_ptr<Mesh>  mMesh;
    std::weak_ptr<Shader> mShader;
public:
    RenderMesh(std::weak_ptr<Mesh> mesh, std::weak_ptr<Shader> shader);
    ~RenderMesh();
    virtual void Execute() override;
};




// BELOW IS NO LONGER BEING USED

// **************************************
// *** TEXTURED MESH ***



class RenderTexturedMesh : public RenderCommand {

private: 
    // Weak pointers don't assume ownership
    // Great for data that has chance of not existing  
    std::weak_ptr<Mesh>  mMesh;
    std::weak_ptr<Shader> mShader;
    std::weak_ptr<Texture> mTexure;
public:
    RenderTexturedMesh(std::weak_ptr<Mesh> mesh,  std::weak_ptr<Texture> texture, std::weak_ptr<Shader> shader);
    ~RenderTexturedMesh();
    virtual void Execute() override;
};