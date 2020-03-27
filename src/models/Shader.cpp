#include <models/Shader.h>

void Shader::linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader) {
    char infoLog[512];
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

    glUseProgram(0);
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

Shader::Shader(char* vShaderFile, char* gShaderFile, char* fShaderFile = "") {

    GLuint vShader = 0;
    GLuint fShader = 0;
    GLuint gShader = 0;

    vShader = loadShader(GL_VERTEX_SHADER, vShaderFile);
    fShader = loadShader(GL_FRAGMENT_SHADER, vShaderFile);

    if (gShaderFile) 
        gShader = loadShader(GL_GEOMETRY_SHADER, gShaderFile);
    
    linkProgram(vShader, gShader, fShader);

}   