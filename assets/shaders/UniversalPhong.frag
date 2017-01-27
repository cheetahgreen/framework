#version 330 core

in VSOut
{
    vec3 Normal;
    vec2 TexCoord;
    vec3 ViewDirection;
    vec3 ViewLightDirection;
} vsOut;

out vec4 color;

uniform sampler2D TextureSlot1;

uniform vec3 LightColor;

uniform vec3 EmissionColor;
uniform vec4 SolidColor;
uniform vec4 DiffuseMapColor;

void main(void)
{
    vec3 lightDirection = normalize(vsOut.ViewLightDirection);
    vec3 normal = normalize(vsOut.Normal);

    float diffuse = dot(lightDirection, normal);

    vec3 albedo = SolidColor.rgb
        + DiffuseMapColor.rgb * texture(TextureSlot1, vsOut.TexCoord).rgb;

    vec3 ambientLight = vec3(0.0, 0.0, 0.0);
    vec3 ambientPart = clamp(albedo * ambientLight, 0, 1);
    vec3 diffusePart = clamp(albedo * diffuse, 0, 1);

    float specularStrength = 0.5f;
    vec3 viewDir = normalize(vsOut.ViewDirection);
    vec3 reflectDir = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * vec3(1.0, 1.0, 1.0);

    color = vec4(EmissionColor + ambientPart + diffusePart + specular, SolidColor.a);
    color.rgb = pow(color.rgb, vec3(1/2.2));
}

