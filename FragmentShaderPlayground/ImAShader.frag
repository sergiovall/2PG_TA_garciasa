#version 330
 
out vec4 fragColor;


void main()
{ 
		fragColor = vec4(tan((gl_FragCoord.x+gl_FragCoord.y)/40),0,0,0);
}
