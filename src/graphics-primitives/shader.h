#pragma once
#include <string>
#include <unordered_map>
#include <glm/mat4x4.hpp>
#include <glad/glad.h>


class Shader {
private:
    int mProgramId;
    std::unordered_map<std::string, GLint> mUniforms;
    bool mShaderActive;

public:
    ~Shader();
    Shader(const std::string& vertex, const std::string& fragment);
    bool IsBound();
    void BoundWarning();
    void Bind();
    void UnBind();
    GLint GetUniformLocation(const std::string& name);
    void Set1Float(float value, const std::string& name);
    void SetMat4(const glm::mat4& matrix, const std::string& name);
    void Set1Int(int value, const std::string& name);

    // uniform functions to come
};


    