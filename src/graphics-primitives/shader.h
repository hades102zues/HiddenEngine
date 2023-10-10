#pragma once
#include <string>
#include <unordered_map>


class Shader {
private:
    int mProgramId;
    std::unordered_map<std::string, int> mUniforms;

public:
    ~Shader();
    Shader(const std::string& vertex, const std::string& fragment);
    void Bind();
    void UnBind();
    int GetUniformLocation(const std::string& name);


    // uniform functions to come
};


    