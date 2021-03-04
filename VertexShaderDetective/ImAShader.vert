#version 330

layout (location=0) in vec3 a_position;

void main()
{
	mat4 Scale(float x, float y, float z){
		
}
	vec3 move = vec3(-0.12, 0.15, 0);
	gl_Position = vec4(Translate * Rotate * Scale * a_position, 3);
}