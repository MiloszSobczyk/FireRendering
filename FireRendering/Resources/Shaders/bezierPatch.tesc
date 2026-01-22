#version 460 core

layout(vertices = 16) out;

uniform float u_tessellationLevel;

void main()
{
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;

	gl_TessLevelOuter[0] = u_tessellationLevel;
	gl_TessLevelOuter[1] = u_tessellationLevel;
	gl_TessLevelOuter[2] = u_tessellationLevel;
	gl_TessLevelOuter[3] = u_tessellationLevel;
        
	gl_TessLevelInner[0] = u_tessellationLevel;
	gl_TessLevelInner[1] = u_tessellationLevel;
}