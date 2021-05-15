#include <HORCHATA/horchata_shader.h>

HORCHATA::Shader::Shader(){}

HORCHATA::Shader::~Shader(){}

void HORCHATA::Shader::loadSource(const Type shader_type, 
	const char * source, 
	const unsigned int source_size)
{

	switch (shader_type) {

	case kType_Fragment:
		shader_id = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	case kType_Geometry:
		shader_id = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	case kType_Vertex:
		shader_id = glCreateShader(GL_VERTEX_SHADER);
		break;
	default:
		shader_id = glCreateShader(GL_INVALID_ENUM);
	}

	GLint size = source_size;
	
	glShaderSource(shader_id, 1, &source, &size);


}

bool HORCHATA::Shader::compile(EDK3::scoped_array<char>* output_log)
{

	glCompileShader(shader_id);
	

	if (!is_compiled()) {

		if (NULL != output_log) {

			GLint log_size = 0;
			glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_size);

			output_log->alloc(log_size);

			glGetShaderInfoLog(shader_id, log_size, NULL, output_log->get());

		}


	}


	return is_compiled();
	
}

bool HORCHATA::Shader::is_compiled() const
{
	GLint compiled;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled);

	return compiled == GL_TRUE;
}

const EDK3::dev::Shader::Type HORCHATA::Shader::type() const
{
	GLint shader_type;
	Type res;

	glGetShaderiv(shader_id, GL_SHADER_TYPE, &shader_type);

	switch (shader_type)
	{
	case GL_FRAGMENT_SHADER:
		res = EDK3::dev::Shader::kType_Fragment;
		break;
		case GL_GEOMETRY_SHADER:
		res = EDK3::dev::Shader::kType_Geometry;
		break;
		case GL_VERTEX_SHADER:
		res = EDK3::dev::Shader::kType_Vertex;
		break;

	}

	return res;

}

unsigned int HORCHATA::Shader::internal_id() const
{
	return shader_id;
}


