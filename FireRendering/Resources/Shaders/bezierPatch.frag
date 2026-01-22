#version 460 core

layout(location = 0) out vec4 FragColor;

in FS_IN
{
    vec3 worldPos;
    vec2 texCoords;
    vec3 normal;
    vec3 tangent;
    vec3 bitangent;
} i;

uniform vec4 u_color;

uniform vec3 u_lightPositions[2] = vec3[](
    vec3(-3.0, -3.0, -3.0),
    vec3(+3.0, +3.0, +3.0)
);

uniform float u_shininess = 64.0;
uniform float u_specularStrength = 1.0;

void main()
{
    vec3 ambient = 0.1 * u_color.rgb;

    vec3 norm = normalize(i.normal);

    vec3 result = ambient;

    for (int n = 0; n < 2; ++n)
    {
        vec3 lightDir = normalize(u_lightPositions[n] - i.worldPos);

        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * u_color.rgb;

        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(norm, reflectDir), 0.0), u_shininess);
        vec3 specular = u_specularStrength * spec * vec3(1.0);

        result += diffuse + specular;
    }

    FragColor = vec4(result, u_color.a);
}
