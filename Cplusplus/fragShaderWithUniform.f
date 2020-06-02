#version 330 core
in vec4 vertexColor;
out vec4 FragColor;
uniform vec4 ourColor;

void main()
{
	FragColor = 1 * vertexColor;
	//FragColor = ourColor * vertexColor;
}
