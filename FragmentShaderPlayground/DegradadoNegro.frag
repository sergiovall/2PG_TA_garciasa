#version 330
 
out vec4 fragColor;
float i = 0;

void main()
{ 
	i = gl_FragCoord.x / 1280;
	fragColor = vec4(i, i, i, 1);  
}
