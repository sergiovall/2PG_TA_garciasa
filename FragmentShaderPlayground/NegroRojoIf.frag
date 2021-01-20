#version 330
 
out vec4 fragColor;


void main()
{ 
	if(gl_FragCoord.x < 1280 / 2){
		fragColor = vec4(0, 0, 0, 1); 
	}else{
		fragColor = vec4(1, 0, 0, 1);
 	}
}
