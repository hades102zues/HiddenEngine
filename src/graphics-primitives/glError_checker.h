#pragma once
#include <glad/glad.h>
#include "../engine-core/logger/logger.h"


void GlErrorChecker(const char* filename, int lineNumber) {
    GLenum errorCode;

    while ((errorCode = glGetError()) != GL_NO_ERROR) {
        std::string error;
        switch (errorCode) {
            case GL_INVALID_ENUM:                   error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                  error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:              error = "INVALID_OPERATION"; break;
            case GL_OUT_OF_MEMORY:                  error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:  error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }

        HIDDEN_ERROR("GlErrorChecker Triggered:- \n\t Error: {} \n\t File: {} \n\t Line: {}", error.c_str(), filename, std::to_string(lineNumber).c_str());
    }

    //HIDDEN_ASSERT(errorCode != GL_NO_ERROR, "GL Errors Occured.");
}


#ifndef HIDDEN_CONFIG_RELEASE
    #define HIDDEN_GL_ERROR_CHECK() GlErrorChecker(__FILE__, __LINE__)
#else
    #define HIDDEN_GL_ERROR_CHECK() (void*)0
#endif