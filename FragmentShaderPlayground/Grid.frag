#version 330
 
out vec4 fragColor;
float i;


void main()
{ 
i = abs(round(max(sin(gl_FragCoord.x/10) ,cos(gl_FragCoord.y/10)))-1);
		fragColor = vec4(i, i, i, 1);
}
