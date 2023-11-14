#include <assimp/Importer.hpp>     
#include <assimp/scene.h>           
#include <assimp/postprocess.h>     
#include <string>
#include "mesh.h"
#include "texture.h"
#include <memory>
#include <vector>
#include <unordered_map>



class ModelLoader {
private:

    std::string mModelName;
    std::string mModelRootDirectory;

    std::vector<std::shared_ptr<Mesh>> mMeshes;
    std::unordered_map<std::string, unsigned int> mKnownLoadedMaps;
    std::unordered_map<unsigned int, std::shared_ptr<Texture>> mTextures;


    void ProcessNode(aiNode* node, const aiScene* scene);
    void ProcessMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<unsigned int> LoadMaps(aiMaterial* material, aiTextureType type, MapType mType);

    
public:
    ModelLoader();
    ~ModelLoader();
    void LoadModel(const std::string& name, const std::string& path);
    
    std::vector<std::shared_ptr<Mesh>> GetMeshes();
    std::unordered_map<std::string, unsigned int> GetKnownLoadedMaps();
    std::unordered_map<unsigned int, std::shared_ptr<Texture>> GetTextures();



};