#ifndef _SHADER_H_
#define _SHADER_H_

#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <exception>

class shader {
public:
    unsigned int ID;    // the shader program ID
    shader(const char* vertexPath, const char* fragmentPath);   // constructor that reads and build 
                                                                // the shader program
    void use();     // use the shader program
    void unuse();
    
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFLoat(const std::string &name, float value) const;
};

#endif