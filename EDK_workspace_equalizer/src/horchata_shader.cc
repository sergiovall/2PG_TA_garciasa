#include <HORCHATA/horchata_shader.h>
#include <EDK3/dev/opengl.h>

void HORCHATA::Shader::loadSource(const Type shader_type, const char * source, const unsigned int source_size)
{

	GLuint shader = glCreateShader(shader_type);
	GLsizei size = source_size;
	GLint i_need_this_for_some_reason;

	glGetShaderiv(shader, shader_type, &i_need_this_for_some_reason);
	glShaderSource(shader, size, &source, &i_need_this_for_some_reason);



}

bool HORCHATA::Shader::compile(EDK3::scoped_array<char>* output_log)
{

	glCompileShader(shader);

	GLint compile_info;
	
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_info);

	return false;
	
}


