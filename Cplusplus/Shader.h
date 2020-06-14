#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader {
public:
	//program ID
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath);
	
	void use();
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	void SetFloat4(const std::string& name, float x, float y, float z, float a) const;
	void SetMat4(const std::string& name, const glm::mat4& mat) const;
private:
	void ValidateShaderOrProgram(
		unsigned int shader,
		void (*getIv)(GLuint shader, GLenum glenum, GLint* success),
		void (*getInfoLog)(GLuint shader, GLsizei size, GLsizei* length, GLchar* infoLog));
	void ValidateShaderProgram(unsigned int shader);
	void ValidateShader(unsigned int shader);


};

#endif
