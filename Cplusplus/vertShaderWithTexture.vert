#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord; // Location svarer til hvad de er bundet til jo!!

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

void main()
{
//    gl_Position = transform * vec4(aPos, 1.0);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}