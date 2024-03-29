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

    // Momentarily bind the texture to GPU unit 0 to apply operations
    // If you do not manually bind the texture, then opengl will auto
    // bind the latest generated textureID to GL_Texture0 --with control to unbind no longer in your hands.
    glActiveTexture(GL_TEXTURE0);
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

    
    // Forward the image data into the Texure object on the GPU memory
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    // GPU generates scaled down versions
    glGenerateMipmap(GL_TEXTURE_2D);

    HIDDEN_INFO("Pushed Texture: <Name : {}, ID : {}>", mTextureName, mTextureId);

    // unbind
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind(int index = 0) {
    // Select texture unit on the GPU to be used
    glActiveTexture(GL_TEXTURE0 + index);

    // Bind the texture to the active unit
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