#version 460 core
out vec4 FragColor;

in vec2 v_UV;

uniform float u_life;
uniform float u_time;

// Simple 2D noise
float hash(vec2 p)
{
    return fract(sin(dot(p, vec2(127.1,311.7))) * 43758.5453);
}

float noise(vec2 p)
{
    vec2 i = floor(p);
    vec2 f = fract(p);

    float a = hash(i);
    float b = hash(i + vec2(1,0));
    float c = hash(i + vec2(0,1));
    float d = hash(i + vec2(1,1));

    vec2 u = f*f*(3.0-2.0*f);
    return mix(a, b, u.x) +
           (c - a)*u.y*(1.0 - u.x) +
           (d - b)*u.x*u.y;
}

void main()
{
    vec2 uv = v_UV * 2.0 - 1.0; // center
    float r = length(uv);
    uv.y += noise(uv + u_time) * 0.3;

    // shape
    float mask = smoothstep(1.0, 0.2, r);

    // animated noise
    float n = noise(uv * 3.0 + vec2(0, u_time * 2.0));
    float flicker = noise(uv * 6.0 + u_time * 4.0);

    float intensity = mask * n * flicker;
    intensity *= u_life; // fade as particle dies

    // Fire color ramp
    vec3 color =
        mix(vec3(1.0, 0.2, 0.0),   // orange
        vec3(1.0, 1.0, 0.2),       // yellow
        intensity);

    // Core white
    color = mix(color, vec3(1.0), pow(intensity, 3.0));

    FragColor = vec4(color, intensity);
}
