#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 vertexColor;

void main()
{
	mat3 m = mat3(
		1, 0, 0,
		0, -1, 0,
		0, 0, 1
	);
	gl_Position = vec4(m * aPos, 1.0);
	vertexColor = aColor;
}
