#version 460 core
out vec4 FragColor;

in vec2 v_UV;

uniform float u_life;
uniform float u_time;
uniform sampler2D u_dissolveTexture;
uniform sampler2D u_dissolveTexture2;
uniform sampler2D u_dissolveTexture3;
uniform float u_random;

uniform vec3 u_colorStart;
uniform vec3 u_colorMid;
uniform vec3 u_colorEnd;

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
    vec2 uv = v_UV * 2.0 - 1.0;

    // sample noise (scrolling upward)
    vec2 noiseUV = v_UV * 2.0 + vec2(0.0, u_time * 0.5);

    vec2 randOffset = vec2(u_random, u_random * 5);
    float n1 = mixNoises(noiseUV + randOffset);

    // distortion
    uv.y += (n1 - 0.5) * 0.3;

    float r = length(uv);

    // shape
    float base = length(uv);
	float edgeNoise = texture(u_dissolveTexture3, v_UV*3.0 + u_time ).r;

	float mask = smoothstep(
		1.0,
		0.2 + edgeNoise*0.4,
		base
	);

    // second noise layer (flicker)
    float n2 = mixNoises(v_UV * 5.0 + u_time * 1.5 + randOffset);

    float intensity = mask * n1 * n2;
    intensity *= u_life;

    vec3 color = mix(u_colorStart, u_colorMid, intensity);
    color = mix(color, u_colorEnd, pow(intensity, 3.0));

    FragColor = vec4(color, intensity);
}
