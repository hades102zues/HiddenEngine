#include "shader.h"
#include <glad/glad.h>
#include "../engine-core/logger/logger.h"
#include "glError_checker.h"
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string& vertex, const std::string& fragment) {
    mProgramId = glCreateProgram();

    int status;
    char errorLog[512];
    unsigned int fragmentShaderId;
    unsigned int vertexShaderId;




    // ******
    // *** Vertex Shader Object
    {
        vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        const GLchar* vSource = vertex.c_str();
        glShaderSource(vertexShaderId, 1, &vSource, NULL);
        glCompileShader(vertexShaderId);
        glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &status);

        if(!status) {
            glGetShaderInfoLog(vertexShaderId, 512, NULL, errorLog);
            HIDDEN_ERROR("Vertex shader failed compilation :: {}", errorLog);
        } else {
            glAttachShader(mProgramId, vertexShaderId);
            
        }
    }

    // ******
    // *** Fragment Shader Object
    {
        fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
        const GLchar* fSource = fragment.c_str();
        glShaderSource(fragmentShaderId, 1, &fSource, NULL);
        glCompileShader(fragmentShaderId);
        glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &status);

        if(!status) {
            glGetShaderInfoLog(fragmentShaderId, 512, NULL, errorLog);
            HIDDEN_ERROR("Fragment shader failed compilation :: {}", errorLog);
        } else {
            glAttachShader(mProgramId, fragmentShaderId);
            
        }
    }



    glLinkProgram(mProgramId);
    glValidateProgram(mProgramId);
    glGetProgramiv(mProgramId, GL_LINK_STATUS, &status);
    if(!status) {
        glGetProgramInfoLog(mProgramId, 512, NULL, errorLog);
        HIDDEN_ERROR("Shader Program failed Linking :: {}", errorLog);
        mProgramId = -1;
    }

    

    // Cleanup after Linking
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId); 

}

void Shader::Bind() {
    glUseProgram(mProgramId);
}

void Shader::UnBind() {
    glUseProgram(0);
    
}

GLint Shader::GetUniformLocation(const std::string& name) {
    auto it = mUniforms.find(name);

    // if the name is not in the list
    if(it == mUniforms.end()) {
        mUniforms[name] = glGetUniformLocation(mProgramId, name.c_str());
    }

    return mUniforms[name];
}

void Shader::Set1Float(float value, const std::string& name) {
    GLint id = GetUniformLocation(name);
    glUniform1f(id, static_cast<GLfloat>(value)); 
}

void Shader::SetMat4(glm::mat4 matrix, const std::string& name) {
    GLint id = GetUniformLocation(name);
    glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(matrix)); 
}

Shader::~Shader() {
    UnBind();
    glDeleteProgram(mProgramId);
}
