#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord; //Cord from other shader

uniform sampler2D ourTexture; //Uniform to accept texture

void main()
{
    FragColor = texture(ourTexture, TexCoord);
}