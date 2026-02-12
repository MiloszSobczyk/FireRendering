#version 460 core
out vec4 FragColor;

in vec2 v_UV;

uniform float u_life;
uniform float u_time;
uniform vec4 u_color;

uniform sampler2D u_noise1;
uniform sampler2D u_noise2;
uniform sampler2D u_noiseDetail;

void main()
{
    vec2 uv = v_UV * 2.0 - 1.0;

    float dist = length(uv);

    float radialMask = smoothstep(1.0, 0.2, dist);

    vec2 flowUV = v_UV * 1.5;
    flowUV.y += u_time * 0.15;

    float baseNoise = texture(u_noise1, flowUV).r;

    vec2 flowUV2 = v_UV * 2.5;
    flowUV2 += vec2(
        sin(u_time * 0.2) * 0.1,
        u_time * 0.1
    );

    float secondaryNoise = texture(u_noise2, flowUV2).r;

    vec2 detailUV = v_UV * 6.0 + u_time * 0.3;
    float detail = texture(u_noiseDetail, detailUV).r;

    float density = baseNoise * 0.6 + secondaryNoise * 0.3 + detail * 0.2;

    density = smoothstep(0.2, 0.8, density);

    density *= radialMask;

    density *= u_life;

    float finalAlpha = density * u_color.a;
    
    FragColor = vec4(u_color.rgb, finalAlpha);
}
