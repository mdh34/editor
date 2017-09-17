
#ifndef SHADERPROG_H
#define SHADERPROG_H

#include "Util.h"

#include <stdlib.h>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>

#include <SDL2/SDL.h>

#ifdef _WIN32
    #include <GL/glew.h>
#else
    #include <OpenGL/gl3.h>
#endif

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

typedef struct ShaderProgram {
ShaderProgram();
	ShaderProgram(std::string vertSource, std::string fragSource);
	ShaderProgram(std::string path);

    std::string path;
    
	int programID;
	int vertexShaderID;
	int fragmentShaderID;

    std::unordered_map <std::string, GLint > uniforms;

	int createShader(char* source, GLenum type);

	void init(char* vert, char* frag);
	void bind();
	void unbind();
	void createUniform(std::string name);
	void setUniform(std::string name, int value);
    void setUniform(std::string name, glm::vec3& value);
    void setUniform(std::string name, glm::vec4& value);
    void setUniform(std::string name, glm::mat4 value);

	void cleanup();
} ShaderProgram;

#endif
