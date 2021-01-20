#version 330
 
out vec4 fragColor;


void main()
{ 
		fragColor = vec4(step(1280.0/2,gl_FragCoord.x), 0, 0, 1);
}
