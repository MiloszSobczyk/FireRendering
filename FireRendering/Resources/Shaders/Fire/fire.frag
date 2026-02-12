#version 460 core
out vec4 FragColor;

in vec2 v_UV;

uniform float u_life;
uniform float u_time;
uniform sampler2D u_dissolveTexture;
uniform sampler2D u_dissolveTexture2;
uniform sampler2D u_dissolveTexture3;

float mixNoises(vec2 uv)
{
    float blend = smoothstep(0.8, 1.2, u_life);
    return mix(
        texture(u_dissolveTexture,  uv).r,
        texture(u_dissolveTexture2, uv).r,
        blend
    );
}

void main()
{
    vec2 uv = v_UV * 2.0 - 1.0; // center

    // sample noise (scrolling upward)
    vec2 noiseUV = v_UV * 2.0 + vec2(0.0, u_time * 0.5);

    float n1 = mixNoises(noiseUV);

    // distortion
    uv.y += (n1 - 0.5) * 0.3;

    float r = length(uv);

    // shape
    float mask = smoothstep(1.0, 0.2, r);

    // second noise layer (flicker)
    float n2 = mixNoises(v_UV * 5.0 + u_time * 1.5);

    float intensity = mask * n1 * n2;
    intensity *= u_life;

    // Fire color ramp
    vec3 color = mix(
        vec3(1.0, 0.2, 0.0),
        vec3(1.0, 1.0, 0.2),
        intensity
    );

    // Core white
    color = mix(color, vec3(1.0), pow(intensity, 3.0));

    FragColor = vec4(color, intensity);
}
