#version 330 core

in VSOut
{
    vec2 TexCoord;
    vec3 Color;
} vsOut;

out vec4 outColor;

uniform sampler2D TextureSlot1;
uniform vec3 EmissionColor;

void main(void)
{
    outColor = vec4(EmissionColor, 1.0);
}
