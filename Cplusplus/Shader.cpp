#include <Shader.h>

	
//class Shader {
//public:
	//unsigned int ID;
	Shader::Shader(const char* vertexPath, const char* fragmentPath) {
		// 1. retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
		try
		{
			//open
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			//read buffer into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			//Close handler
			vShaderFile.close();
			fShaderFile.close(); //  why not in a final block ??? //Because of RAII (Resource acquisition is initialization). ifstreams deconstructor will be call end of scope, or after exception
			//convert to string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		//convert to C string
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		//Create shaders
		unsigned int vertex, fragment;
		//Vertex
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		ValidateShader(vertex);
		//Fragment
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		ValidateShader(fragment);
		//Program
		ID = glCreateProgram();

		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);

		ValidateShaderProgram(ID);
		//DELETE SHADERS
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	void Shader::use() {
		glUseProgram(ID);
	}
	void Shader::SetBool(const std::string& name, bool value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void Shader::SetInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void Shader::SetFloat(const std::string& name, float value) const {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	void Shader::SetFloat4(const std::string& name, float x, float y, float z, float a) const {
		glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, a);
	}

	void Shader::SetMat4(const std::string& name, glm::mat4* mat) const {
		unsigned int transformLoc = glGetUniformLocation(ID, name.c_str());
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(*mat));
	}

	//TODO: Deconstructor with delete program?

	void Shader::ValidateShader(unsigned int shader) {
		ValidateShaderOrProgram(shader, glGetShaderiv, glGetShaderInfoLog);
	}

	void Shader::ValidateShaderProgram(unsigned int shader) {
		ValidateShaderOrProgram(shader, glGetProgramiv, glGetProgramInfoLog);
	}

	void Shader::ValidateShaderOrProgram(
		unsigned int shader, 
		void (*getIv)(GLuint shader, GLenum glenum, GLint *success), 
		void (*getInfoLog)(GLuint shader, GLsizei size, GLsizei *length, GLchar *infoLog))
	{
		int success;
		char infoLog[512]; //TODO: Figure out if this is being created 3 times due to 3 calls ... Probably insignificant
		getIv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			getInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_COMPILED\n" << infoLog << std::endl;
		}
	}

