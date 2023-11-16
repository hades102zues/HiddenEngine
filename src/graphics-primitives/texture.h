#pragma once
#include <string>

enum class MapType {
    AMBIENT = 0,
    DIFFUSE,
    SPECULAR
};

class Texture {
private:
    unsigned int mTextureId;
    const char* mTexturePath;
    const char* mTextureName;
    MapType mMapType;
    
public:
    Texture();
    Texture(const char* name, const std::string& path, MapType type);
    unsigned int GetTextureId();
    MapType GetTextureType();
    void LoadTexture();
    void Bind(int index);
    void UnBind();
    ~Texture();
};