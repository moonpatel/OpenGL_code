#include "shader.h"

shader::shader(const char* vertexPath, const char* fragmentPath) {
    // retrieve the vertex fragment source code from filepath
    std::string vertexCode,fragmentCode;
    std::ifstream vShaderFile, fShaderFile;

    // ensure ifstream objects can throw exceptions
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

try {
    // open files
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);
    std::stringstream vShaderStream, fShaderStream;
    // read the file's contents into the streams
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    // close file handlers
    vShaderFile.close();
    fShaderFile.close();
    // convert stream into string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
}
catch(std::ifstream::failure e) {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
}
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // COMPILE SHADERS
    unsigned int vertex, fragment;
    int success;
    char infoLog[1024];

    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex,1,&vShaderCode,NULL);
    glCompileShader(vertex);
    // print compile errors, if any
    glGetShaderiv(vertex,GL_COMPILE_STATUS,&success);
    if(!success) {
        glGetShaderInfoLog(vertex,1024,NULL,infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment,1,&fShaderCode,NULL);
    glCompileShader(fragment);
    // print compile errors, if any
    glGetShaderiv(fragment,GL_COMPILE_STATUS,&success);
    if(!success) {
        glGetShaderInfoLog(fragment,1024,NULL,infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // shader program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    // print linking errors, if any
    glGetProgramiv(ID,GL_LINK_STATUS,&success);
    if(!success) {
        glGetProgramInfoLog(ID, 1024,NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // delete shaders
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void shader::use() {
    glUseProgram(ID);
}

void shader::unuse() {
    glUseProgram(0);
}

void shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID,name.c_str()),(int)value);
}
void shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID,name.c_str()), value);
}
void shader::setFLoat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID,name.c_str()), value);
}