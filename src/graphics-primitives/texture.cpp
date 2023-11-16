#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <glad/glad.h>
#include "../engine-core/logger/logger.h"
#include "../common/path_dict.h"
#include <filesystem>

Texture::Texture() {
    HIDDEN_WARN("Call made to incorrect Texture constructor.");
    mTextureName = "";
    mTexturePath = "";
}

Texture::Texture(const char* name, const std::string& path, MapType type = MapType::DIFFUSE) {
    mTextureName = name;
    mTexturePath = path.c_str();
    mMapType = type;

    LoadTexture();
}
void Texture::LoadTexture() {

    // Create blank texture object ON System Mem
    glGenTextures(1, &mTextureId);
    glBindTexture(GL_TEXTURE_2D, mTextureId);


    // Retrieve Texture data
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(mTexturePath, &width, &height, &nrChannels, 0);

    if(!data) {
        
        HIDDEN_WARN("Failed to load texure:- \n\tfile_name: {} \n\tfile_path: {}", mTextureName, mTexturePath);
        return;
    }


    // Determine the color channels
    GLenum format;
    if (nrChannels == 1)
        format = GL_RED;
    else if (nrChannels == 3)
        format = GL_RGB;
    else if (nrChannels == 4)
        format = GL_RGBA;


    // What to do when text coords fall outside the textures dimensions
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    // What method should be used to retrieve the color from the texture (upscaled/downscaled/mipmaps)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    
    // Forward the texture object to GPU memory
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    // GPU generates scaled down versions
    glGenerateMipmap(GL_TEXTURE_2D);

    HIDDEN_INFO("Pushed Texture: <{}, {}>", mTextureName, mTextureId);
}

void Texture::Bind(int index = 0) {
    // Select texture unit on the GPU to temporarily hold your texture for sampling
    glActiveTexture(GL_TEXTURE0 + index);

    // Select an already forwarded texture to be assigned to currently active texture unit
    glBindTexture(GL_TEXTURE_2D, mTextureId);

    // Update a fragment sampler with the index of the unit having the texture.
    // If a fragment sampler is not set then Opengl "might" default to 0 unit.


}
unsigned int Texture::GetTextureId() {
    return mTextureId;
}

MapType Texture::GetTextureType() {
    return mMapType;
}
void Texture::UnBind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
Texture::~Texture() {
    UnBind();
    glDeleteTextures(1, &mTextureId);
}