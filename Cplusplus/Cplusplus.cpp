// Cplusplus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <glad/glad.h> 
#include <GLFW\glfw3.h>
#include <iostream>
#include <Shader.h>
#include <Renderer.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);

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

float rectangle[] = {
	// positions          // colors           // texture coords
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};
unsigned int rectIndices[] = {
	0,1,2,
	2,3,0
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
	Shader shader3("D:\\Projects\\Cplusplus\\Cplusplus\\vertShaderWithTexture.vert", "D:\\Projects\\Cplusplus\\Cplusplus\\fragShaderWithTexture.frag");

	//TEXTURE
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set texture wrapping/filtering options.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//Load and generate texture
	int width, height, nrChannels;
	unsigned char* data = stbi_load("D:\\Projects\\Cplusplus\\Assets\\container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D/* generate tex to currently bound target*/, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}	
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data); // FREE DATA. we in c++ BUD

		//TEXTURE
	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// set texture wrapping/filtering options.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//Load and generate texture
	//int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data2 = stbi_load("D:\\Projects\\Cplusplus\\Assets\\awesomeface.png", &width, &height, &nrChannels, 0);
	if (data2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA /* NOTE! this is PNG, so add alpha channel*/, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data2); // FREE DATA. we in c++ BUD


	//First triagle
	Renderer objectA(vertices, sizeof(vertices), indices, sizeof(indices) / sizeof(indices[0]));
	//Second
	Renderer ObjectB(vertices2, sizeof(vertices2), 3);
	//Third
	Renderer ObjectC(vertices3, sizeof(vertices3), 3);
	Renderer Rect(rectangle, sizeof(rectangle), rectIndices, sizeof(rectIndices) / sizeof(rectIndices[0]), 3);

	////Uncomment to draw as wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // rotate 90 around z;
	//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

	while (!glfwWindowShouldClose(window))
	{
		process_input(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/// Use time to make it osciliate between green and black
		auto timevalue = glfwGetTime();
		float greenValue = (float)(sin(timevalue) / 2.0f) + 0.5f;
		//We can find the uniform before using the shader program
		
		glm::mat4 model{ glm::mat4(1.0f) };
		glm::mat4 view{ glm::mat4(1.0f) };
		glm::mat4 projection{ glm::mat4(1.0f) };

		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // rotation around x, lay it down.
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); // move scene backwards.

		projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f); //TODO: 800/600 in variables
		shader3.use();
		shader3.SetInt("texture1", 0);
		shader3.SetInt("texture2", 1);
		shader3.SetMat4("projection", &projection);
		shader3.SetMat4("view", &view);
		shader3.SetMat4("model", &model);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);//TODO: REFACTOR THIS IN...
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		Rect.Render();


		//shader1.use();
		//shader1.SetFloat("posX", sin(timevalue) * 1.5f);
		//shader1.SetFloat4("ourColor", 1.0f, greenValue, 0, 1);
		//// But we have to use the shader before setting it.

		//objectA.Render();
		//shader2.use();
		//ObjectB.Render();
		//ObjectC.Render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//glDeleteProgram(shaderProgram);

	glfwTerminate(); // Call to free resources
    std::cout << "Window closed.\n";
}


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
