#include <assimp/Importer.hpp>     
#include <assimp/scene.h>           
#include <assimp/postprocess.h>     
#include <string>
#include "textured_mesh.h"
#include "texture.h"
#include <memory>
#include <vector>
#include <unordered_map>



class Model {
private:

    std::string mModelName;
    std::string mModelRootDirectory;

    std::vector<std::shared_ptr<TexturedMesh>> mMeshes;

     // <texture name, texture_ref>
    std::unordered_map<std::string, std::weak_ptr<Texture>> mKnownLoadedMaps;


    void ProcessNode(aiNode* node, const aiScene* scene);
    void ProcessMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<std::weak_ptr<Texture>> LoadMaps(aiMaterial* material, aiTextureType type, MapType mType);


    // this mTextures is pretty useless, isn't be taken advantage of and should be rremoved
    std::vector<std::shared_ptr<Texture>> mTextures;

   
    
public:
    Model();
    ~Model();
    void LoadModel(const std::string& name, const std::string& path);
    
    std::vector<std::shared_ptr<TexturedMesh>> GetMeshes();
    std::unordered_map<std::string, std::weak_ptr<Texture>> GetKnownLoadedMaps();
    std::vector<std::shared_ptr<Texture>>  GetTextures();



};