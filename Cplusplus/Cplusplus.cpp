// Cplusplus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <glad/glad.h> 
#include <GLFW\glfw3.h>
#include <iostream>
#include <Shader.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);
void BindTriangle(GLuint *VAO, GLuint  *VBO, float *vertices, int len);
//void ValidateShaderCompiled(unsigned int shader, bool isProgram);

//float vertices[] = {
//	// first triangle
//	 0.5f,  0.5f, 0.0f,  // top right
//	 0.5f, -0.5f, 0.0f,  // bottom right
//	-0.5f,  0.5f, 0.0f,  // top left 
//	// second triangle
//	 0.5f, -0.5f, 0.0f,  // bottom right
//	-0.5f, -0.5f, 0.0f,  // bottom left
//	-0.5f,  0.5f, 0.0f   // top left
//}; // Example of poorly optimized triangle

float vertices[] = {
	-0.4f, -0.3f, 0.0f, //0
	-0.3f, -0.1f, 0.0f, //1
	-0.2f, -0.3, 0.0f, //2 
	-0.2f, 0.1f, 0.0f, // 3
	-0.1f, -0.1f, 0.0f,// 4
	0.0f,  -0.3f, 0.0f // 5
};//rectangle stored in NDC(normalized Display coordinates)

float vertices3[] = {
	// Positions       //Colors
	-0.1f, -0.1f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.1f, 0.0f,   0.0f, 1.0f, 0.0f,
	0.1f, -0.1f,0.0f,   0.0f, 0.0f, 1.0f
};
float vertices2[] = {
	0.1f, -0.1f,0.0f, 0.0f, 0.0f, 1.0f,
	0.2f, 0.1f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.3f, -0.1f, 0.0f,1.0f, 0.0f, 0.0f
};

unsigned int indices[] = {  // note that we start from 0!
	0, 1, 2,   // first triangle
	1, 3, 4,    // second triangle
	2,4,5,
};

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //This line is only for macOS

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // sets rezie callback
	glViewport(0, 0, 800, 600); // sets the viewport. Could make smaller viewport to render ui or other elements in window


	Shader shader1("D:\\Projects\\Cplusplus\\Cplusplus\\vertexShader1.v", "D:\\Projects\\Cplusplus\\Cplusplus\\fragShaderWithUniform.f");
	Shader shader2("D:\\Projects\\Cplusplus\\Cplusplus\\vertShaderColor.v", "D:\\Projects\\Cplusplus\\Cplusplus\\fragShaderColor.f");
	//Shader shader2("D:\\Projects\\Cplusplus\\Cplusplus\\vertexShader1.v", "D:\\Projects\\Cplusplus\\Cplusplus\\fragShader.f");

	//TEXTURE
	int width, height, nrChannels;
	unsigned char* data = stbi_load("D:\\Projects\\Cplusplus\\Assets\\container.jpg", &width, &height, &nrChannels, 0);
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D/* generate tex to currently bound target*/, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data); // FREE DATA. we in c++ BUD

	//Triangle preperation:
	unsigned int VBO[3], VAO[3];
	unsigned int EBO; 

	glGenBuffers(3, VBO);
	glGenVertexArrays(3, VAO);

	//First triagle
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]); //Bind it
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Static, as implied, set once, used many times
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // starts at 0

	glGenBuffers(1, &EBO); //ELEMENT BUFFER OBJECTS
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	

	//Second
	BindTriangle(&VAO[1], &VBO[1], vertices2, sizeof(vertices2));
	std::cout << sizeof(vertices3)/sizeof(vertices3[0]) << std::endl;
	BindTriangle(&VAO[2], &VBO[2], vertices3, sizeof(vertices3)/sizeof(vertices3[0]));
	//Third
	glBindVertexArray(VAO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]); //Bind it
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW); //Static, as implied, set once, used many times

	// position attrib
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // starts at 0
	glEnableVertexAttribArray(0);
	// color attrib
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	////Uncomment to draw as wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!glfwWindowShouldClose(window))
	{
		process_input(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/// Use time to make it osciliate between green and black
		auto timevalue = glfwGetTime();
		float greenValue = (sin(timevalue) / 2.0f) + 0.5f;
		//We can find the uniform before using the shader program

		shader1.use();
		shader1.SetFloat("posX", sin(timevalue) * 1.5);
		shader1.SetFloat4("ourColor", 0.0f, greenValue, 0, 1);
		// But we have to use the shader before setting it.

		glBindVertexArray(VAO[0]);
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(indices[0]), GL_UNSIGNED_INT, 0); //Use EBO to draw rect

		shader2.use();
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(VAO[2]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO[0]);
	glDeleteVertexArrays(1, &VAO[1]);
	glDeleteBuffers(1, &VBO[0]);
	glDeleteBuffers(1, &VBO[1]);
	//glDeleteProgram(shaderProgram);

	glfwTerminate(); // Call to free resources
    std::cout << "Window closed.\n";
}

void BindTriangle(GLuint  *VAO, GLuint  *VBO, float *vertices, int len)
{
	glBindVertexArray(*VAO);
	glBindBuffer(GL_ARRAY_BUFFER, *VBO); //Bind it
	glBufferData(GL_ARRAY_BUFFER, len, vertices2, GL_STATIC_DRAW); //Static, as implied, set once, used many times

	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW); //Static, as implied, set once, used many times
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // starts at 0
	glEnableVertexAttribArray(0);
	//enable colors now
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

//void ValidateShaderCompiled(unsigned int shader, bool isProgram)
//{
//	//check is success
//	int success;
//	char infoLog[512];
//	if (isProgram) {
//		glGetProgramiv(shader, GL_LINK_STATUS, &success);
//	}
//	else {
//		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//	}
//	if (!success)
//	{
//		if (isProgram) {
//			glGetProgramInfoLog(shader, 512, NULL, infoLog);
//		}
//		else {
//			glGetShaderInfoLog(shader, 512, NULL, infoLog);
//		}
//		std::cout << "ERROR::SHADER::COMPILATION::FAILED\n" << infoLog << std::endl;
//	}
//}

void process_input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
