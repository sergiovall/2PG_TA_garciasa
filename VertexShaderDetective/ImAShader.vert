#version 330

layout (location=0) in vec3 a_position;

void main()
{
	vec3 move = vec3(0, 0, 0);
	vec3 scale = vec3(0.0025, 0.0025, 0.0025);
	gl_Position = vec4(move + scale * a_position, 1.0);
}