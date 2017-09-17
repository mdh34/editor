#include "ShaderProgram.h"
#include "Util.h"
#include "GLError.h"

ShaderProgram::ShaderProgram() {

}

ShaderProgram::ShaderProgram(std::string vertSource, std::string fragSource) {
	init((char*) vertSource.c_str(), (char*) fragSource.c_str());
}

ShaderProgram::ShaderProgram(std::string shaderPath) {
	std::string path = getCWD() + shaderPath;
	std::string vertSource = loadFile(path + ".vert");
	std::string fragSource = loadFile(path + ".frag");

    this->path = shaderPath;
    
	init((char*)vertSource.c_str(), (char*)fragSource.c_str());

	printf("[SUCCESS] Loaded shader %s!\n", path.c_str());
}

void ShaderProgram::init(char* vert, char* frag) {
    
	programID = glCreateProgram();
	if (programID == 0) {
		fprintf(stderr, "[ERROR] Failed to create shader program!\n");
		exit(EXIT_FAILURE);
	}

    fprintf(stderr, "[INFO] Loading %s\n", path.c_str());
	vertexShaderID = createShader(vert, GL_VERTEX_SHADER);
	fragmentShaderID = createShader(frag, GL_FRAGMENT_SHADER);

	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);

	glLinkProgram(programID);
	GLint linked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, &linked);
	if (linked == GL_FALSE) {
		GLint maxLength = 0;

		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);
		fprintf(stderr, "[ERROR] Failed to link shader!\n");

		glDeleteProgram(programID);

		return;
	}
}

int ShaderProgram::createShader(char* shaderSource, GLenum type) {
    if (type == 35633) {
        printf("VERT\n\n");
    } else if (type == 35632) {
        printf("FRAG\n\n");
    }
	GLuint shaderID = glCreateShader(type);
	if (shaderID == 0) {
		fprintf(stderr, "[ERROR] Failed to create shader!\n");
		glDeleteProgram(programID);
		exit(EXIT_FAILURE);
	}
	
	const GLchar *source = (const GLchar *)shaderSource;
	glShaderSource(shaderID, 1, &source, 0);

	glCompileShader(shaderID);

	GLint success = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(shaderID, maxLength, &maxLength, &infoLog[0]);

		fprintf(stderr, "[ERROR] Failed to compile shader!\n");
		for (std::vector<char>::const_iterator i = infoLog.begin(); i != infoLog.end(); ++i)
			fprintf(stderr, "%c", *i);
		
		glDeleteProgram(shaderID);
	}

	return shaderID;
}

void ShaderProgram::bind() {
	glUseProgram(programID);
}

void ShaderProgram::unbind() {
	glUseProgram(0);
}

void ShaderProgram::createUniform(std::string name) {
	GLint uniformLocation = glGetUniformLocation(programID, name.c_str());
	if (uniformLocation < 0) {
		fprintf(stderr, "Failed to find uniform declaration: %s, in shader.\n", name.c_str());
	}
    
    // uniforms[name] = uniformLocation;
    uniforms.emplace(name, uniformLocation);
    printf("%s: %x\n", name.c_str(), uniformLocation);
}

void ShaderProgram::setUniform(std::string name, int value) {
    glUniform1i(uniforms[name], value);
}

void ShaderProgram::setUniform(std::string name, glm::vec3& value) {
	glUniform3f(uniforms[name], value.x, value.y, value.z);
}

void ShaderProgram::setUniform(std::string name, glm::vec4& value) {
	glUniform4f(uniforms[name], value.x, value.y, value.z, value.w);
}

void ShaderProgram::setUniform(std::string name, glm::mat4 value) {
    glUniformMatrix4fv(uniforms[name], 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::cleanup() {
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}
