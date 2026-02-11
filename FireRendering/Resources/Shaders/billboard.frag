#version 460 core

layout(location = 0) out vec4 FragColor;

in vec2 v_UV;

uniform sampler2D u_texture;
uniform sampler2D u_dissolveTex;

uniform vec4 u_color;

uniform float u_time;
uniform float u_dissolveAmount;
uniform float u_dissolveStrength;
uniform float u_tiling;

void main()
{
    vec4 base = texture(u_texture, v_UV);

    vec2 dissolveUV = v_UV * u_tiling;
    dissolveUV += vec2(u_time * 0.2, u_time * 0.15);

    float noise = texture(u_dissolveTex, dissolveUV).r;

    noise = smoothstep(0.2, 0.8, noise);

    float shiftedNoise = clamp(noise + u_dissolveAmount, 0.0, 1.0);

    shiftedNoise = pow(shiftedNoise, 1.5);

    float modulation = mix(1.0, 1.0 - shiftedNoise, u_dissolveStrength);

    vec3 finalColor = base.rgb * u_color.rgb;
    finalColor *= modulation;

    float finalAlpha = base.a * u_color.a;
    finalAlpha *= modulation;

    FragColor = vec4(finalColor, finalAlpha);
}
