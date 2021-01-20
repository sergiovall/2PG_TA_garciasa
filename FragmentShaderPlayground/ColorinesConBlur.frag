#version 330
 
out vec4 fragColor;


void main()
{ 
		fragColor = vec4(0.05*gl_FragCoord.x-(1280/2*0.05), 0.05*gl_FragCoord.y - (720/2*0.05) , 0, 1);
}
