#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 normal;

uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

out vec3 vFragPos;
out vec3 vNormal;

void main()
{
    // World-space fragment position
    vFragPos = vec3(u_modelMatrix * position);

    // Transform normal to world space
    vNormal = normalize(mat3(transpose(inverse(u_modelMatrix))) * normal.xyz);

    gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * position;
}
