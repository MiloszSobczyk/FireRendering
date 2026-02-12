#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 aTexCoord;

out vec2 v_UV;

uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_modelMatrix;
uniform vec3 u_cameraWorldPos;
uniform vec3 u_velocityDir = vec3(0.f, 1.f, 0.f);

void main()
{
    v_UV = aTexCoord;

    vec3 center = vec3(u_modelMatrix[3]);

    vec3 forward = normalize(u_cameraWorldPos - center);

    vec3 vel = normalize(u_velocityDir);
    vec3 up = normalize(vel - forward * dot(vel, forward));

    if (length(up) < 0.001)
    {
        up = vec3(0.0, 1.0, 0.0);
    }

    vec3 right = normalize(cross(up, forward));
    up = cross(forward, right);


    float scaleX = length(u_modelMatrix[0].xyz);
    float scaleY = length(u_modelMatrix[1].xyz);

    vec3 worldPos =
        center +
        right * position.x * scaleX +
        up    * position.y * scaleY;

    gl_Position = u_projectionMatrix * u_viewMatrix * vec4(worldPos, 1.0);
}
