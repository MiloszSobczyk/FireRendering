#version 460 core

layout(location = 0) out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D u_texture;
uniform vec4 u_color = vec4(1.f);

void main()
{
    vec4 texColor = texture(u_texture, TexCoord);
    FragColor = texColor * u_color;
}
