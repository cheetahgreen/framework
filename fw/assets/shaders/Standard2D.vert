#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 color;

out VSOut
{
    vec2 TexCoord;
    vec3 Color;
} vsOut;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main(void)
{
    vec4 modelPosition = model * vec4(position, 0.0, 1.0);
    gl_Position = proj * view * modelPosition;
    vsOut.TexCoord = texCoord;
    vsOut.Color = color;
}
