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

unsigned int MyCustomMaterial::num_attributes_required() const
{
	return 2;
}

EDK3::Attribute MyCustomMaterial::attribute_at_index(const unsigned int attrib_idx) const
{
	switch (attrib_idx) {
	case 0: 
	return EDK3::Attribute::A_POSITION;
	break;
	case 1:
	return EDK3::Attribute::A_NORMAL;

	break;
	}
}

EDK3::Type MyCustomMaterial::attribute_type_at_index(const unsigned int attrib_index) const
{
	return EDK3::Type::T_FLOAT_3;
}
