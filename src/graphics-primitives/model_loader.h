#include <assimp/Importer.hpp>     
#include <assimp/scene.h>           
#include <assimp/postprocess.h>     
#include <string>
#include "mesh.h"
#include "texture.h"
#include <memory>


class ModelLoader {
private:
    Vertex mVertices;
    unsigned int mIndices;
    //std::unique_ptr<Texture> mTextures;
    std::unique_ptr<Mesh> mMesh;

    
public:
    ModelLoader();
    ~ModelLoader();
    void LoadModel(const std::string& filePath);
    // Mesh GetMesh();


};