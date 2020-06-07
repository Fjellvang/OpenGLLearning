#pragma once
#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <iostream>


class Renderer
{
public:
	unsigned int *VBO, *VAO;
	unsigned int EBO; 
	Renderer(float *vertArray, int vertSize, float *indicesArray, int indicesSize);
	///
	/// Case of colors defined in vert array
	///
	Renderer(float *vertArray, int vertSize, int colorStart);
	virtual void Render();
private:
	bool useEBO;
	int indicesLen;
};

