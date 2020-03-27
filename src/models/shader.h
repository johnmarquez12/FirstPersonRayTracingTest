#pragma once 

#define GLEW_STATIC
#include <GL/include/glew.h>
#include <GLFW/include/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <logger/log.h>
#include <variant>

class Shader {

    public:
        Shader(char* vShaderFile, char* fShaderFile, char* gShaderFile);

        ~Shader() {
            glDeleteProgram(this->id);
        }

        inline GLuint GetId() const {
            return id;
        }

        // Functions to set uniforms 
        template <typename T> void setUniform(T val, const GLchar* name, GLboolean transpose = GL_FALSE);

        void setVec3f(glm::fvec3 value, const GLchar* name);
        void setVec2f(glm::fvec2 value, const GLchar* name);
        void setFloat(GLfloat value, const GLchar* name);
        void setMat4f(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE);
        void setMat3f(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE);

    private:
        GLuint id;
        std::string loadShaderSource(char* filename);
        GLuint loadShader(GLenum type, char* filename);
        void linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader);

        inline void use() { glUseProgram(this->id); };
        inline void unUse() { glUseProgram(0); };
};

