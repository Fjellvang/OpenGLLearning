#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord; //Cord from other shader

uniform sampler2D texture1; //Uniform to accept multiple textures
uniform sampler2D texture2; //Uniform to accept multiple textures

void main()
{
//    FragColor = texture(ourTexture, TexCoord) * vec4(ourColor,1);
    FragColor = mix(texture(texture1, TexCoord),texture(texture2, TexCoord),0.2);
}