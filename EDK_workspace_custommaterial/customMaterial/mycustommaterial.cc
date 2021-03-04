#include "..\include\YO\mycustommaterial.h"

MyCustomMaterial::MyCustomMaterial()
{
}

bool MyCustomMaterial::load_shaders(EDK3::ref_ptr<EDK3::dev::Shader> vertex_shader, EDK3::ref_ptr<EDK3::dev::Shader> fragment_shader)
{

	if (vertex_shader == nullptr || fragment_shader == nullptr) {
		return false;
	}
	
	EDK3::ref_ptr<EDK3::dev::Program> program;
	EDK3::dev::GPUManager::Instance()->newProgram(&program);
	set_program(program);

	
	if (vertex_shader->compile() && fragment_shader->compile()) {

		get_program()->attach(vertex_shader.get());
		get_program()->attach(fragment_shader.get());
		get_program()->link();

		return true;

	}

	return false;

}

bool MyCustomMaterial::enable(const EDK3::MaterialSettings *) const
{
	if (get_program() == nullptr) {
		return false;
	}

	get_program()->use();

	return true;

}
