#version 330
 
out vec4 fragColor;
float i;


void main()
{ 
i = 0;
if(-gl_FragCoord.x+1000 == gl_FragCoord.y || gl_FragCoord.x-280 == gl_FragCoord.y){
i = 1;
}

		fragColor = vec4(i, i, 0, 1);
}
