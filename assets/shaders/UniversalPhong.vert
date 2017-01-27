#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 texCoord;

out VSOut
{
    vec3 Normal;
    vec2 TexCoord;
    vec3 ViewDirection;
    vec3 ViewLightDirection;
} vsOut;

uniform vec3 LightDirection;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(void)
{
    vec4 viewPosition = view * model * vec4(position, 1.0f);
    gl_Position = projection * viewPosition;

    vsOut.TexCoord = texCoord.xy;

    vsOut.Normal = normalize(
        (view * (transpose(inverse(model)) * vec4(normal, 0))).xyz
    );

    vsOut.ViewDirection = normalize(-viewPosition.xyz);
    vsOut.ViewLightDirection = normalize((view * vec4(LightDirection, 0)).xyz);
}
