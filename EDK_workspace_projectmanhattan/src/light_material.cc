#include <HORCHATA/light_material.h>
#include <EDK3/materialsettings.h>
#include <EDK3/dev/shader.h>
#include <EDK3/dev/gpumanager.h>
#include <EDK3/dev/program.h>
#include <ESAT/math.h>
#include <ESAT/time.h>
#include <EDK3/dev/opengl.h>

int LightMaterial::textures_loaded_ = 0;

LightMaterial::LightMaterial(){


}

bool LightMaterial::enable(const EDK3::MaterialSettings *mat_settings) const
{
	
	get_program()->use();
	LightMaterial::Settings* mat = (Settings*)mat_settings;

	if (mat->texture() != nullptr) {

		int color_id = get_program()->get_uniform_position("u_color");
		get_program()->set_uniform_value(color_id, EDK3::T_FLOAT_3, mat->color());

		int time_id = get_program()->get_uniform_position("u_time");
		const float time = ESAT::Time() * 0.0025f;
		get_program()->set_uniform_value(time_id, EDK3::T_FLOAT_1, &time);

		if (mat->light_pos()) {

			int light_pos_id = get_program()->get_uniform_position("u_light_position");
			get_program()->set_uniform_value(light_pos_id, EDK3::T_FLOAT_3, mat->light_pos());

		}

		if (mat->camera_position()) {

			int camera_pos_id = get_program()->get_uniform_position("u_camera_pos");
			get_program()->set_uniform_value(camera_pos_id, EDK3::T_FLOAT_3, mat->camera_position());

		}
		
		if (mat->fog()) {

			int fog_enabled_id = get_program()->get_uniform_position("u_fog_enabled");
			get_program()->set_uniform_value(fog_enabled_id, EDK3::T_INT_1, mat->fog());
		}

		int bright_id = get_program()->get_uniform_position("u_mat_bright");
		get_program()->set_uniform_value(bright_id, EDK3::T_FLOAT_1, &mat->shininesh_);

		int texture_color_id = get_program()->get_uniform_position("u_texture_color");
		get_program()->set_uniform_value(texture_color_id, EDK3::T_UINT_1, (int *)0);

		if (mat->fog_color()) {

			int fog_color_id = get_program()->get_uniform_position("u_fog_color");
			get_program()->set_uniform_value(fog_color_id, EDK3::T_FLOAT_3, mat->fog_color());

		}

		

	}
	return false;
}

void LightMaterial::setupCamera(const float projecton[16], const float view[16]) const
{

	const ESAT::Mat4 vp_matrix = ESAT::Mat4Multiply(ESAT::Mat4FromColumns(projecton), ESAT::Mat4FromColumns(view));

	int u_vp_matrix_uniform_id = get_program()->get_uniform_position("u_vp_matrix");

	get_program()->set_uniform_value(u_vp_matrix_uniform_id, EDK3::T_MAT_4x4, vp_matrix.d);

}

void LightMaterial::setupModel(const float m[16]) const
{

	int program_id = get_program()->get_uniform_position("u_m_matrix");
	if (program_id >= 0) {
		get_program()->set_uniform_value(program_id, EDK3::T_MAT_4x4, m);
	}

}

unsigned int LightMaterial::num_attributes_required() const
{
	return 3;
}

EDK3::Attribute LightMaterial::attribute_at_index(const unsigned int attrib_idx) const
{
	switch (attrib_idx) {

	case 0: 
		return EDK3::A_POSITION;
		break;
	case 1:
		return EDK3::A_NORMAL;
		break;
	case 2:
		return EDK3::A_UV;
		break;
	default:
		return EDK3::A_MAX_INDEX_NUMBER;


	}
}

EDK3::Type LightMaterial::attribute_type_at_index(const unsigned int attrib_index) const
{
	
	return EDK3::T_FLOAT_3;

}

EDK3::dev::Program* LightMaterial::get_program()
{
	return program_.get();
}

const EDK3::dev::Program * LightMaterial::get_program() const
{
	return program_.get();
}

bool LightMaterial::load_shaders(EDK3::ref_ptr<EDK3::dev::Shader> vertex_shader, EDK3::ref_ptr<EDK3::dev::Shader> fragment_shader)
{
	bool ok = false;

	ok = vertex_shader->compile();
	ok = fragment_shader->compile();

	EDK3::dev::GPUManager::Instance()->newProgram(&program_);
	set_program(program_);

	program_->attach(vertex_shader.get());
	program_->attach(fragment_shader.get());

	program_->link();

	return ok;

}

void LightMaterial::set_program(EDK3::ref_ptr<EDK3::dev::Program> program)
{

	program_ = program;

}

bool LightMaterial::load_shaders_from_filepaths(const char * vertex_shader_path, const char * fragment_shader_path)
{
	
	EDK3::ref_ptr<EDK3::dev::Shader> vertex;
	EDK3::ref_ptr<EDK3::dev::Shader> fragment;

	loadVertexShaderFile(&vertex, vertex_shader_path);
	loadVertexShaderFile(&fragment, fragment_shader_path);

	return load_shaders(vertex, fragment);


}

/*LightMaterial & LightMaterial::operator=(const LightMaterial &)
{
	// TODO: insertar una instrucción return aquí
}*/

