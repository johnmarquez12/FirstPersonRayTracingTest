#include <models/Shader.h>

void Shader::linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader) {
    GLint success;

    this->id = glCreateProgram();
    glAttachShader(this->id, vertexShader);
    glAttachShader(this->id, fragmentShader);

    if (geometryShader)
        glAttachShader(this->id, geometryShader);

    glLinkProgram(this->id);

    glGetProgramiv(this->id, GL_LINK_STATUS, &success);

    if (!success) {
        CORE_WARN("ERROR::Shader could not link program\n");
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(geometryShader);
}


std::string Shader::loadShaderSource(char* filename) {
    std::string temp = "";
    std::string src = "";

    std::ifstream inFile;

    inFile.open(filename);

    if (inFile.is_open()) {
        while (std::getline(inFile, temp))
            src += temp + "\n";
    } else {
        CORE_WARN("Error::Shader could not open file {}\n", filename);
    }

    inFile.close();

    return src;
}

GLuint Shader::loadShader(GLenum type, char* filename) {
    char infoLog[512];
    GLint success;

    GLuint shader = glCreateShader(type);
    const GLchar* src = this->loadShaderSource(filename).c_str();
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
        CORE_WARN("ERROR::Shader Could not compile shader {}\n", filename);
    }

    return shader;
}

Shader::Shader(char* vShaderFile, char* fShaderFile, char* gShaderFile) {

    GLuint vShader = 0;
    GLuint fShader = 0;
    GLuint gShader = 0;

    vShader = loadShader(GL_VERTEX_SHADER, vShaderFile);
    fShader = loadShader(GL_FRAGMENT_SHADER, vShaderFile);

    if (gShaderFile) 
        gShader = loadShader(GL_GEOMETRY_SHADER, gShaderFile);
    
    linkProgram(vShader, gShader, fShader);

}   

void Shader::setVec3f(glm::fvec3 value, const GLchar* name)  {
    use();

    glUniform3fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

    unUse();
}

void Shader::setVec2f(glm::fvec2 value, const GLchar* name)  {
    use();

    glUniform3fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

    unUse();
}

void Shader::setFloat(GLfloat value, const GLchar* name)  {
    use();

    glUniform1f(glGetUniformLocation(this->id, name), value);

    unUse();
}

void Shader::setMat4f(glm::mat4 value, const GLchar* name, GLboolean transpose)  {
    use();

    glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

    unUse();
}

void Shader::setMat3f(glm::mat3 value, const GLchar* name, GLboolean transpose)  {
    use();

    glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

    unUse();
}

template <typename T> void Shader::setUniform(T val, const GLchar* name, GLboolean transpose) {

    this->use();

    if (std::is_same_v<T, glm::fvec3>) 
        glUniform3fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(val));
    else if (std::is_same_v<T, glm::fvec2>) 
        glUniform2fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(val));
    else if (std::is_same_v<T, GLfloat>)
        glUniform1f(glGetUniformLocation(this->id, name), val);
    else if (std::is_same_v<T, glm::mat4>)
        glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(val));
    else if (std::is_same_v<T, glm::mat3>)
        glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(val));   
    else 
        CORE_ERROR("ERROR::Shader Incompatible Type in Function setUniform \n"); 
    this->unUse();
}
