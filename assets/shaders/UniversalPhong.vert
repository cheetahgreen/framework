#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 texCoord;

out VSOut
{
    vec3 Normal;
    vec2 TexCoord;
} vsOut;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(void)
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    vsOut.TexCoord = vec2(texCoord.x, texCoord.y);
    vsOut.Normal = (transpose(inverse(model)) * vec4(normal, 0)).xyz;
}
