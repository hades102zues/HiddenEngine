#pragma once
#include <string>


class Texture {
private:
    unsigned int mTextureId;
    const char* mTexturePath;
    const char* mTextureName;
public:
    Texture();
    Texture(const char* name, const std::string& path);
    void LoadTexture();
    void Bind();
    void UnBind();
    ~Texture();
};