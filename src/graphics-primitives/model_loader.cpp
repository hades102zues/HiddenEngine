#include "model_loader.h"
#include "../engine-core/logger/logger.h"  
#include "../common/path_dict.h" 



ModelLoader::ModelLoader () {
    HIDDEN_INFO("A model loader was created");
    
}

void ModelLoader::LoadModel(const std::string& path) {
    std::string fullPath = pathLibrary.ProjectRoot + path;
}

// Mesh ModelLoader::GetMesh() {

// }


ModelLoader::~ModelLoader() {

}