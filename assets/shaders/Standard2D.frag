#version 330 core

in VSOut
{
    vec2 TexCoord;
    vec3 Color;
} vsOut;

out vec4 outColor;

uniform sampler2D TextureSlot1;

uniform vec4 DiffuseMapTintColor;
uniform vec3 EmissionColor;

void main(void)
{
    vec4 textureColor =
        DiffuseMapTintColor * texture(TextureSlot1, vsOut.TexCoord);

    outColor = vec4(textureColor.rgb, 1.0) + vec4(EmissionColor, 0);
}
