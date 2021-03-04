#include <A/mat_cust.h>
#include <EDK3/dev/shader.h>
#include <EDK3/dev/gpumanager.h>
#include <EDK3/dev/program.h>

AndresMatCustom::AndresMatCustom()
{
}

bool AndresMatCustom::load_shaders(EDK3::ref_ptr<EDK3::dev::Shader> vertex_shader, EDK3::ref_ptr<EDK3::dev::Shader> fragment_shader)
{

	if (vertex_shader == nullptr || fragment_shader == nullptr) {
		return false;
	}

	EDK3::ref_ptr<EDK3::dev::Program> program;
	EDK3::dev::GPUManager::Instance()->newProgram(&program);
	set_program(program);

	bool compiled = vertex_shader->compile() && fragment_shader->compile();

	if (compiled) {
		get_program()->attach(vertex_shader.get());
		get_program()->attach(fragment_shader.get());
		get_program()->link();
	}
	
	return compiled;
}

bool AndresMatCustom::enable(const EDK3::MaterialSettings*) const{

	get_program()->use();

	return true;

}

AndresMatCustom::~AndresMatCustom()
{
}
