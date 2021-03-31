#version 330
 
uniform sampler2D u_colorTexture;

out vec4 fragColor;
in vec3 pos;
in vec2 uv;

void main() { 
 
	fragColor = texture(u_colorTexture, pos.xy);	
 }
