#version 330
 
out vec4 fragColor;


void main()
{ 
		fragColor = vec4(gl_FragCoord.x-(1280/2), 0, 0, 1);
}
