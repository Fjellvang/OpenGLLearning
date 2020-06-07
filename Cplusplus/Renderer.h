#pragma once
#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <iostream>


class Renderer
{
public:
	unsigned int VBO[1], VAO[1];
	unsigned int EBO; 
	Renderer(float vertArray[], unsigned long long vertSize, unsigned int *indicesArray, unsigned long long indicesSize);
	~Renderer();
	///
	/// Case of colors defined in vert array
	///
	Renderer(float *vertArray, unsigned long long vertSize, int colorStart);
	virtual void Render();
private:
	bool useEBO;
	int indicesLen;
};

