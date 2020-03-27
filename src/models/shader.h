#pragma once 

#include <GL/include/glew.h>
#include <GLFW/include/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <string>
#include <fstream>
#include <logger/log.h>

class Shader {

    public:
        Shader(char* vShaderFile, char* gShaderFile, char* fShaderFile = "");

        ~Shader() {
            glDeleteProgram(id);
        }

        inline GLuint GetId() const {
            return id;
        }

        // Functions to set uniforms 

    private:
        GLuint id;
        std::string loadShaderSource(char* filename);
        GLuint loadShader(GLenum type, char* filename);
        void linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader);
};

