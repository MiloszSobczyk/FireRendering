#version 460 core
out vec4 FragColor;

in vec2 v_UV;

uniform float u_life;

uniform vec3 u_colorStart;
uniform vec3 u_colorMid;
uniform vec3 u_colorEnd;

void main()
{
    vec2 uv = v_UV * 2.0 - 1.0;
    float dist = length(uv);

    float radial = smoothstep(1.0, 0.0, dist);

    float intensity = pow(radial, 0.5);
    intensity *= u_life * 1.2;

    vec3 color = mix(u_colorStart, u_colorMid, intensity);
    color = mix(color, u_colorEnd, pow(intensity, 3.0));

    float alpha = clamp(intensity, 0.0, 0.8);

    FragColor = vec4(color, alpha);
}
