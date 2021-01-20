#version 330
 
out vec4 fragColor;


void main()
{ 
		fragColor = vec4(sin(gl_FragCoord.x/20), 0, 0, 1);
}
