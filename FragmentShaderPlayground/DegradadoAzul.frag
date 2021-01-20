#version 330
 
out vec4 fragColor;

float i = 0;
float j = 0;

void main()
{ 
	i = gl_FragCoord.x / 1280;
	j = gl_FragCoord.y / 720;
	fragColor = vec4(i, j, 1, 1);  
}
