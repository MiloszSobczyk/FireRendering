#version 460 core
out vec4 FragColor;

in vec2 v_UV;

uniform float u_life;

void main()
{
    vec2 uv = v_UV * 2.0 - 1.0;
    float dist = length(uv);

    // Radial falloff (soft circular particle)
    float radial = smoothstep(1.0, 0.0, dist);

    // Boost intensity: raise to a power for stronger core
    float intensity = pow(radial, 0.5); // soft core
    intensity *= u_life * 1.2;          // reduce multiplier for darker appearance

    vec3 darkRed      = vec3(0.25, 0.03, 0.0); // darker base
    vec3 brightOrange = vec3(0.7, 0.3, 0.05);  // less saturated
    vec3 yellowWhite  = vec3(0.9, 0.8, 0.5);   // slightly dimmed

    vec3 color = mix(darkRed, brightOrange, intensity);
    color = mix(color, yellowWhite, pow(intensity, 3.0));

    float alpha = clamp(intensity, 0.0, 0.8); // cap alpha below 1 for subtle blending

    FragColor = vec4(color, alpha);

}
