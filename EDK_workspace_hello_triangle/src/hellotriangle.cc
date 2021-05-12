#include <ESAT/window.h>
#include <ESAT/input.h>
#include <ESAT/time.h>
#include <EDK3/dev/opengl.h>
#include <EDK3/dev/gpumanager.h>


// References
//https://www.khronos.org/registry/OpenGL-Refpages/gl4/

/*
#version 330

uniform vec3 hola;
layout (location=0) in vec3 quetal;

void main()
{
   gl_Position = ;
}



#version 330

out vec4 fragColor;

void main()
{
	fragColor = ;
}
*/


// openGL names 
GLuint triangle_vertices_ID;
GLuint triangle_indices_ID;
GLuint vertex_shader_ID;
GLuint fragment_shader_ID;
GLuint program_ID;


float vertices[] = { 0.0f,0.5f,0.0f,
					-0.5f,0.0f,0.0f,
					0.5f,0.0f,0.0f
};

unsigned int indices[] = { 0,1,2,1,0,2 };

const char* vertexString = {
	"#version 330											\n"
	"layout(location =  0) in vec3 a_position;				\n"
	"void main(){											\n"
	"gl_Position = vec4(a_position, 1.0f);					\n"
	"}														\n"

};

const char* fragmentString = {
	"#version 330											\n"
	"uniform float time_;									\n"
	"out vec4 fragColor;									\n"
	"void main(){											\n"
	"float fade_x = gl_FragCoord.x / 1280;\n"
	"fragColor = vec4(mix(1.0f,0.0f,fade_x+cos(time_*0.001)),mix(0.7f,0.0f,fade_x+cos(time_*0.001)),mix(0.0f,1.0f,fade_x+cos(time_*0.001)), 1.0f);					\n"
	"}														"

};

void prepare() {



	glGenBuffers(1, &triangle_vertices_ID);
	glGenBuffers(1, &triangle_indices_ID);

	glBindBuffer(GL_ARRAY_BUFFER, triangle_vertices_ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangle_indices_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,NULL);
	glEnableVertexAttribArray(0);

	program_ID = glCreateProgram();

	vertex_shader_ID = glCreateShader(GL_VERTEX_SHADER);
	fragment_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertex_shader_ID, 1, &vertexString, NULL);
	glShaderSource(fragment_shader_ID, 1, &fragmentString, NULL);

	glCompileShader(vertex_shader_ID);
	glCompileShader(fragment_shader_ID);

	glAttachShader(program_ID, vertex_shader_ID);
	glAttachShader(program_ID, fragment_shader_ID);

	glLinkProgram(program_ID);
	glUseProgram(program_ID);
	

}

void render_function(float time) {

	GLint time_id;
	time_id = glGetUniformLocation(program_ID, "time_");
	glUniform1f(time_id,time);
	
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT ,NULL );

}


int ESAT::main(int argc, char **argv) {

	ESAT::WindowInit(1280, 720);
	prepare();

	while (ESAT::WindowIsOpened() && !ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape)) {

		render_function((float)ESAT::Time());
		ESAT::WindowFrame();
	}

	// MAGIC

	return 0;
}











/*
float vertices[] = { 0.0f,0.5f,0.0f,
					0.5f,0.0f,0.0f,
					-0.5f,0.0f,0.0f,
					1.0f,0.0f,0.0f,
					0.0f,0.0f,0.0f,
					0.0f,0.0f,0.0f };

unsigned int indices[] = { 0,2,1,0,1,2 };

const char* vertices_string = {
	"#version 330									\n"
	"layout(location = 0) in vec3 a_position;		\n"
	"layout(location = 1) in vec3 a_color;			\n"
	"out vec3 color;								\n"
	"void main(){									\n"
	"gl_Position = vec4(a_position,1.0f);			\n"
	"color = a_color;}								\n"


};

const char* fragment_string = {
	"#version 330										\n"
	"out vec4 fragColor;								\n"
	"in vec3 color;										\n"
	"void main(){										\n"
	"fragColor = vec4(color,1.0f);						\n"
	"}"
};


void prepare() {


	glGenBuffers(1, &triangle_vertices_ID);
	glGenBuffers(1, &triangle_indices_ID);

	glBindBuffer(GL_ARRAY_BUFFER, triangle_vertices_ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangle_indices_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)(9 * sizeof(float)));
	glEnableVertexAttribArray(1);

	vertex_shader_ID = glCreateShader(GL_VERTEX_SHADER);
	fragment_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertex_shader_ID,1,&vertices_string,NULL);
	glShaderSource(fragment_shader_ID, 1, &fragment_string, NULL);

	program_ID = glCreateProgram();

	glCompileShader(vertex_shader_ID);
	glCompileShader(fragment_shader_ID);

	glAttachShader(program_ID, vertex_shader_ID);
	glAttachShader(program_ID, fragment_shader_ID);

	glLinkProgram(program_ID);
	glUseProgram(program_ID);
}


void render_function() {

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	vertices[1] += cos(ESAT::Time() *0.01) * 0.01;
	vertices[4] += cos(ESAT::Time() *0.01) * 0.01;
	vertices[7] += cos(ESAT::Time() *0.01) * 0.01;

	vertices[3] = sin(ESAT::Time() * 0.0025) * 0.25;
	vertices[6] = -sin(ESAT::Time() * 0.0025) * 0.25;

	glBindBuffer(GL_ARRAY_BUFFER, triangle_vertices_ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	

	glUseProgram(program_ID);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}*/







/*
float vertices[] = { 0.0f,0.5f,0.0f,
				0.5f,0.0f,0.0f,
				-0.5f,0.0f,0.0f,
				1.0f , 0.0f, 0.0f,
				1.0f, 0.0f, 0.0f,
				1.0f, 0.0f, 0.0f };
unsigned int indices[] = { 0, 2, 1 };

const char* vertex_string = { 
	"#version 330										\n"
	"layout(location = 0) in vec3 a_position;			\n"
	"layout(location = 1) in vec3 a_color;				\n"
	"out vec3 color;									\n"
	"void main()										\n"
	"{													\n"
	"gl_Position = vec4(a_position, 1.0f);				\n"
	"color = a_color;									\n"
	"}"
};

const char* fragment_string = {
	"#version 330										\n"
	"out vec4 fragColor;								\n"
	"in vec3 color;										\n"
	"void main(){										\n"
	"fragColor = vec4(color,1.0f);						\n"
	"}"

};



void prepare() {

	// LET'S
	glGenBuffers(1, &triangle_vertices_ID);
	glGenBuffers(1, &triangle_indices_ID);

	glBindBuffer(GL_ARRAY_BUFFER, triangle_vertices_ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,triangle_indices_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

	

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(9 * sizeof(float)));
	glEnableVertexAttribArray(1);

	vertex_shader_ID = glCreateShader(GL_VERTEX_SHADER);
	fragment_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertex_shader_ID, 1, &vertex_string, NULL);
	glShaderSource(fragment_shader_ID, 1, &fragment_string, NULL);
	
	program_ID = glCreateProgram();

	glCompileShader(vertex_shader_ID);
	glCompileShader(fragment_shader_ID);
	

	glAttachShader(program_ID, vertex_shader_ID);
	glAttachShader(program_ID, fragment_shader_ID);

	glLinkProgram(program_ID);
	glUseProgram(program_ID);


}

void render_function() {

	// DO
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glUseProgram(program_ID);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}

int ESAT::main(int argc, char **argv) {

	ESAT::WindowInit(1280, 720);
	prepare();

	while (ESAT::WindowIsOpened() && !ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape)) {
		
		render_function();
		ESAT::WindowFrame();
	}

	// MAGIC

	return 0;
}
/*
float position[] = { 0.0f , 0.5f, 0.0f,
					  0.5f, 0.0f, 0.0f,
					  -0.5f, 0.0f, 0.0f,
					  1.0f , 0.0f, 0.0f,
					  1.0f, 0.0f, 0.0f,
					  1.0f, 0.0f, 0.0f };

unsigned int indices[] = { 0, 2, 1,
						   1, 2, 0 };


const char* vertex_string = {
"#version 330                                \n"
"layout(location = 0) in vec3 a_position;    \n"
"layout(location = 1) in vec3 a_color;       \n"
"out vec3 color;                             \n"
"void main()                                 \n"
"{                                           \n"
"gl_Position = vec4(a_position, 1.0f);       \n"
"color = a_color;                            \n"
"}                                           \n"
};

const char* fragment_string = {
"#version 330                                \n"
"out vec4 fragColor;                         \n"
"in  vec3 color;                             \n"
"void main()                                 \n"
"{                                           \n"
"fragColor = vec4(color, 1.0f);              \n"
"}                                           \n"
};


void prepare() {

	glGenBuffers(1, &triangle_vertices_ID);
	glGenBuffers(1, &triangle_indices_ID);

	glBindBuffer(GL_ARRAY_BUFFER, triangle_vertices_ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangle_indices_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(9 * sizeof(float)));
	glEnableVertexAttribArray(1);


	vertex_shader_ID = glCreateShader(GL_VERTEX_SHADER);
	fragment_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertex_shader_ID, 1, &vertex_string, NULL);
	glShaderSource(fragment_shader_ID, 1, &fragment_string, NULL);

	program_ID = glCreateProgram();

	glCompileShader(vertex_shader_ID);
	glCompileShader(fragment_shader_ID);

	glAttachShader(program_ID, vertex_shader_ID);
	glAttachShader(program_ID, fragment_shader_ID);

	glLinkProgram(program_ID);
	glUseProgram(program_ID);

}

void render_function() {

	glClearColor(0.2f,
		0.2f,
		0.2f,
		1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	position[3] = cosf((float)ESAT::Time() * 0.005f) * 0.5f;
	position[5] = sinf((float)ESAT::Time() * 0.005f) * 0.5f;
	position[6] = -cosf((float)ESAT::Time() * 0.005f) * 0.5f;
	position[8] = -sinf((float)ESAT::Time() * 0.005f) * 0.5f;

	glBindBuffer(GL_ARRAY_BUFFER, triangle_vertices_ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_DYNAMIC_DRAW);

	glUseProgram(program_ID);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
*/
/*
int ESAT::main(int argc, char **argv) {

	ESAT::WindowInit(1280, 720);
	prepare();

	while (ESAT::WindowIsOpened() && !ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape)) {

		render_function();
		ESAT::WindowFrame();
	}

	// MAGIC

	return 0;
}*/
