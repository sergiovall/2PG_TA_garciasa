#version 330
 
out vec4 fragColor;


void main()
{ 
		fragColor = vec4(sin(gl_FragCoord.x/20), cos(gl_FragCoord.y/20), 0, 1);
}
