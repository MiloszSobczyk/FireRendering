#version 460 core

in vec3 vFragPos;
in vec3 vNormal;

out vec4 FragColor;

uniform vec4 u_color;
uniform vec3 u_lightPositions[3] = vec3[](vec3(4.0, 4.0, 4.0), vec3(-4.0, 4.0, -4.0), vec3(0.0, -4.0, 0.0));

uniform float u_shininess = 64.0;
uniform float u_specularStrength = 1.0;

void main()
{
    vec3 ambient = 0.1 * u_color.rgb;
    vec3 norm = normalize(vNormal);
    vec3 result = ambient;

    for(int i = 0; i < 3; i++)
    {
        vec3 lightDir = normalize(u_lightPositions[i] - vFragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(norm, reflectDir), 0.0), u_shininess);
        vec3 diffuse = diff * u_color.rgb;
        vec3 specular = u_specularStrength * spec * vec3(1.0);
        result += diffuse + specular;
    }

    FragColor = vec4(result, u_color.a);
}
