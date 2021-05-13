#include <HORCHATA/horchata_program.h>

HORCHATA::Program::Program() {

	program_id = -1;

}

HORCHATA::Program::~Program() {



}

void HORCHATA::Program::attach(EDK3::dev::Shader * shader_id)
{

	if (program_id == -1) {
		
		program_id = glCreateProgram();

	}

	glAttachShader(program_id, shader_id->internal_id());

}

bool HORCHATA::Program::link(EDK3::scoped_array<char>* link_log)
{
	GLint status;
	GLint length;

	glLinkProgram(program_id);
	glGetProgramiv(program_id, GL_LINK_STATUS, &status);

	if (nullptr != link_log) {

		glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &length);

		link_log->alloc(length);
		glGetProgramInfoLog(program_id, length, 0, link_log->get());

	}

	// 1 - gl true
	return status == GL_TRUE;

}

void HORCHATA::Program::use() const
{

	glUseProgram(program_id);

}

int HORCHATA::Program::get_attrib_location(const char * name) const
{
	
	return glGetAttribLocation(program_id, name);

}

int HORCHATA::Program::get_uniform_position(const char * name) const
{
	return glGetUniformLocation(program_id, name);
}

void HORCHATA::Program::set_uniform_value(const int uniform_pos, const EDK3::Type uniform_type, const float * value) const
{

	switch (uniform_type) {
	case EDK3::T_FLOAT_1:
		glUniform1f(uniform_pos, *value);
		break;

	case EDK3::T_FLOAT_2:
		glUniform2f(uniform_pos, value[0], value[1]);
		break;

	case EDK3::T_FLOAT_3:
		glUniform3f(uniform_pos, value[0], value[1], value[2]);
		break;

	case EDK3::T_FLOAT_4:
		glUniform4f(uniform_pos, value[0], value[1], value[2], value[3]);
		break;

	case EDK3::T_MAT_2x2:
		glUniformMatrix2fv(uniform_pos, 1, GL_FALSE, value);
		break;

	case EDK3::T_MAT_3x3:
		glUniformMatrix3fv(uniform_pos, 1, GL_FALSE, value);
		break;

	case EDK3::T_MAT_4x4:
		glUniformMatrix4fv(uniform_pos, 1, GL_FALSE, value);
		break;
	}

}

void HORCHATA::Program::set_uniform_value(const int uniform_pos, const EDK3::Type uniform_type, const int * value) const
{

	switch (uniform_type) {
	case EDK3::T_INT_1:
		glUniform1f(uniform_pos, *value);
		break;

	case EDK3::T_INT_2:
		glUniform2f(uniform_pos, value[0], value[1]);
		break;

	case EDK3::T_INT_3:
		glUniform3f(uniform_pos, value[0], value[1], value[2]);
		break;

	case EDK3::T_INT_4:
		glUniform4f(uniform_pos, value[0], value[1], value[2], value[3]);
		break;

	}

}

void HORCHATA::Program::set_uniform_value(const int uniform_pos, const EDK3::Type uniform_type, const unsigned int * value) const
{

	switch (uniform_type) {
	case EDK3::T_UINT_1:
		glUniform1f(uniform_pos, *value);
		break;

	case EDK3::T_UINT_2:
		glUniform2f(uniform_pos, value[0], value[1]);
		break;

	case EDK3::T_UINT_3:
		glUniform3f(uniform_pos, value[0], value[1], value[2]);
		break;

	case EDK3::T_UINT_4:
		glUniform4f(uniform_pos, value[0], value[1], value[2], value[3]);
		break;

	}

}

unsigned int HORCHATA::Program::internal_id() const
{

	return program_id;

}