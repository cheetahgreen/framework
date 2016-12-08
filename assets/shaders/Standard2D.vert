#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 color;

out VSOut
{
    vec2 TexCoord;
    vec3 Color;
} vsOut;

uniform mat3 model;
uniform mat3 view;
uniform mat4 proj;

void main(void)
{
    gl_Position = vec4(position, 0.0, 1.0);
    vsOut.TexCoord = texCoord;
    vsOut.Color = color;
}
