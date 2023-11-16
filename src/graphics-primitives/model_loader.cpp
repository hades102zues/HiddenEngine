#include "model_loader.h"
#include "../engine-core/logger/logger.h"  
#include "../common/path_dict.h" 



ModelLoader::ModelLoader () {
    HIDDEN_INFO("A model loader was created");
    
}

void ModelLoader::LoadModel(const std::string& name, const std::string& path) {
    

    mModelName = name;
    mModelRootDirectory = path;

    Assimp::Importer importer;

    // pull the whole model scene
    const aiScene *scene = importer.ReadFile(path+name, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        HIDDEN_ERROR("Failed to import model {} : {}", name, importer.GetErrorString()); 
        return;
    }

    
    ProcessNode(scene->mRootNode, scene);
    
    
}

void ModelLoader::ProcessNode(aiNode* node, const aiScene* scene) {

    // Process the node's Meshes
    for (int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        ProcessMesh(mesh, scene);
    }

    // Proces the children Nodes
    for (int i = 0; i < node->mNumChildren; i++) {
        ProcessNode(node->mChildren[i], scene);
    }

}

    // A single model item is usually broken down into a number of sub-meshes
    // This function will parse each submesh

void ModelLoader::ProcessMesh(aiMesh* mesh, const aiScene* scene) {
    


    // *********
    // Consume the geometric data of the Mesh 

    std::vector<Vertex> inVertices;

    for (int i = 0; i < mesh->mNumVertices; i++) {
        glm::vec3 vec3d;

        // *********
        // Vertex Position
        Vertex vertex;
        if (mesh->HasPositions()) {
            vec3d.x = mesh->mVertices[i].x;
            vec3d.y = mesh->mVertices[i].y;
            vec3d.z = mesh->mVertices[i].z;

            vertex.Position = vec3d;
        }  else {

            vertex.Position = glm::vec3(0.0f);
            HIDDEN_WARN("Mesh has no vertex positions");

        }

        
        
        // *********
        // Normal
        if (mesh->HasNormals()) {
            vec3d.x = mesh->mNormals[i].x;
            vec3d.y = mesh->mNormals[i].y;
            vec3d.z = mesh->mNormals[i].z;

            vertex.Normal = vec3d;
        } else {
            vertex.Normal = glm::vec3(0.0f);
            HIDDEN_WARN("Mesh has no normals")

        }


        // *********
        // Texture Coordinates
        if(mesh->mTextureCoords[0]) {
                glm::vec2 vec;

                // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
                // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                vec.x = mesh->mTextureCoords[0][i].x; 
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.TextCoords = vec;


                // Tangent
                // vec3d.x = mesh->mTangents[i].x;
                // vec3d.y = mesh->mTangents[i].y;
                // vec3d.z = mesh->mTangents[i].z;
                // vertex.Tangent = vec3d;

                // Bitangent
                // vec3d.x = mesh->mBitangents[i].x;
                // vec3d.y = mesh->mBitangents[i].y;
                // vec3d.z = mesh->mBitangents[i].z;
                // vertex.Bitangent = vec3d;
        }
        else {
            vertex.TextCoords = glm::vec2(0.0f);
            HIDDEN_WARN("Mesh has no texture coords");
        }



        // *********
        // Store the above data
        inVertices.push_back(vertex);
        

    }


    // *********
    // Consume Indices Data
    // A face represents a single triangle 
    // And for each triangle we need the index of the vertices use to build that triangle

    std::vector<unsigned int> inIndices;
    if (mesh->HasFaces()) {

        for (int i = 0; i < mesh->mNumFaces; i++) {

            aiFace face = mesh->mFaces[i];

            // retrieve all indices for a face and store them
            for(unsigned int j = 0; j < face.mNumIndices; j++) {
                inIndices.push_back(face.mIndices[j]);  
            }
                
        }

    } else {
        HIDDEN_WARN("Mesh has no indices");
    }


    



    // *********
    // Consume Material (textures)
    // Here we expect all models to come with textures and neglect code to grab colors
    // We also expect all textures to be held within the same directory as .obj file and the .mtl file should be modified to specify this as well.
    
    std::vector<std::weak_ptr<Texture>>  inMaps;
    // check if materials exist
    if (mesh->mMaterialIndex >= 0) {


        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex]; 

        // load the diffuse map
        std::vector<std::weak_ptr<Texture>>  diffuseMaps = LoadMaps(material, aiTextureType_DIFFUSE, MapType::DIFFUSE);
        inMaps.insert(inMaps.end(), diffuseMaps.begin(), diffuseMaps.end() );

        //  load the specular map
        std::vector<std::weak_ptr<Texture>>  specularMaps = LoadMaps(material, aiTextureType_SPECULAR, MapType::SPECULAR);
        inMaps.insert(inMaps.end(), specularMaps.begin(), specularMaps.end());

    } else {
        HIDDEN_WARN("Mesh has no materials");
    }





    // *********
    // Store Data
    std::shared_ptr<Mesh> inMesh = std::make_shared<Mesh>(inVertices, inIndices, inMaps, GlDraw::MESH_INDEX_DRAW);
    mMeshes.push_back(inMesh);



}


std::vector<std::weak_ptr<Texture>> ModelLoader::LoadMaps(aiMaterial* material, aiTextureType type, MapType mType) {
    
    std::vector<std::weak_ptr<Texture>> textures;

    for (unsigned int i = 0; i < material->GetTextureCount(type); i++) {

       

        // Typically obj files list the complete path name of the texture. 
        // However, given our modified .mtl files we will only get the name-extension of the texture
        aiString textName; 
        material->GetTexture(type, i, &textName);
        std::string cpTextName = textName.C_Str();

        // check to see if map already loaded
        auto it = mKnownLoadedMaps.find(cpTextName);


        if (it == mKnownLoadedMaps.end()) {
            
            // construct absolute path to texture
            std::string fullPath = mModelRootDirectory + cpTextName;

            // create the texture 
            std::shared_ptr<Texture> tex = std::make_shared<Texture>(textName.C_Str(), fullPath, mType);

            // add to the texture list
            mTextures.push_back(tex);

            // add to the list of know maps
            mKnownLoadedMaps.emplace(cpTextName, tex);

            // add to Mesh's list of textures
            textures.push_back(tex);

        } else {

            // get the texture ref
            auto ref = it->second;

            // add to this Mesh's list of textures
            textures.push_back(ref);

        }

    }

    return textures;
}

std::vector<std::shared_ptr<Mesh>> ModelLoader::GetMeshes() {
    return mMeshes;
}
std::unordered_map<std::string, std::weak_ptr<Texture>> ModelLoader::GetKnownLoadedMaps() {
    return mKnownLoadedMaps;
}
std::vector<std::shared_ptr<Texture>> ModelLoader::GetTextures() {
    return mTextures;
}


ModelLoader::~ModelLoader() {

}