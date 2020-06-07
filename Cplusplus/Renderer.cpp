#include "Renderer.h"

Renderer::Renderer(float* vertArray, int vertSize, float* indicesArray, int indicesSize) {
	glGenBuffers(1, VBO);
	glGenVertexArrays(3, VAO);

	//First triagle
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]); //Bind it

	std::cout << "CHECK SIZE:" << sizeof(vertArray) << std::endl;

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertArray), vertArray, GL_STATIC_DRAW); //Static, as implied, set once, used many times
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // starts at 0

	glGenBuffers(1, &EBO); //ELEMENT BUFFER OBJECTS
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesArray), indicesArray, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);

	indicesLen = indicesSize;
	useEBO = true;
}

Renderer::Renderer(float* vertArray, int vertSize, int colorStart) {
	glGenBuffers(1, VBO);
	glGenVertexArrays(3, VAO);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]); //Bind it
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertArray), vertArray, GL_STATIC_DRAW); //Static, as implied, set once, used many times

	// position attrib
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // starts at 0
	glEnableVertexAttribArray(0);
	// color attrib
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(colorStart * sizeof(float)));
	glEnableVertexAttribArray(1);

	indicesLen = 0;
	useEBO = false;
	EBO = NULL;
}

void Renderer::Render() {
	glBindVertexArray(VAO[0]);
	//TODO: USE Inheritance to avoid this branch.
	if (useEBO)
	{
		glDrawElements(GL_TRIANGLES, indicesLen, GL_UNSIGNED_INT, 0); //Use EBO to draw rect
	}
	else {
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}
