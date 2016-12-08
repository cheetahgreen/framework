#version 330 core

in VSOut
{
    vec2 TexCoord;
    vec3 Color;
} vsOut;

out vec4 outColor;

uniform sampler2D TextureSlot1;

void main(void)
{
    vec4 textureColor = texture(TextureSlot1, vsOut.TexCoord);
    outColor = vec4(textureColor.rgb, 1.0);
}
