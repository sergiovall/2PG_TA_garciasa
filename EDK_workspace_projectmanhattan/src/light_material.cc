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
		get_program()->set_uniform_value(texture_color_id, EDK3::T_UINT_1, (int*) 0);
		
		//FALLO EN LA TEXTURA
		//FALLO EN HORCHATA::SHADER

		if (mat->fog_color()) {

			int fog_color_id = get_program()->get_uniform_position("u_fog_color");
			get_program()->set_uniform_value(fog_color_id, EDK3::T_FLOAT_3, mat->fog_color());

		}

		if (mat->dir_lights()) {
			char text[500];
			int num_dir = mat->num_dir_lights();
			int light_struct_id;
			for (int i = 0; i < num_dir; ++i) {

				snprintf(text, sizeof("u_dir_lights[%d].direction"), "u_dir_lights[%d].direction", i);
				light_struct_id = get_program()->get_uniform_position(text);
				
				get_program()->set_uniform_value(light_struct_id, 
					EDK3::T_FLOAT_3, 
					mat->dir_lights()[i].dir_);

				printf("%s , %d\n", text, mat->dir_lights()[i].dir_);

		
			}

			 for (int i = 0; i < num_dir; ++i) {

				snprintf(text, sizeof("u_dir_lights[%d].ambient"), "u_dir_lights[%d].ambient", i);
				light_struct_id = get_program()->get_uniform_position(text);
				
				get_program()->set_uniform_value(light_struct_id,
					EDK3::T_FLOAT_3, 
					mat->dir_lights()[i].ambient_light_);

				printf("%s , %d\n", text, mat->dir_lights()[i].ambient_light_);

			 
			 }
			 
			 for (int i = 0; i < num_dir; ++i) {
				
				snprintf(text, sizeof("u_dir_lights[%d].diffuse"), "u_dir_lights[%d].diffuse", i);
				light_struct_id = get_program()->get_uniform_position(text);
				
				get_program()->set_uniform_value(light_struct_id, 
					EDK3::T_FLOAT_3, 
					mat->dir_lights()[i].diffuse_light_);

				printf("%s , %d\n", text, mat->dir_lights()[i].diffuse_light_);

			 
			 }
			 
			for (int i = 0; i < num_dir; ++i) {
				
				snprintf(text, sizeof("u_dir_lights[%d].specular"), "u_dir_lights[%d].specular", i);
				light_struct_id = get_program()->get_uniform_position(text);
				
				get_program()->set_uniform_value(light_struct_id, 
					EDK3::T_FLOAT_3, 
					mat->dir_lights()[i].specular_light_);

				printf("%s , %d\n", text, mat->dir_lights()[i].specular_light_);

			 
			}
			 
			for (int i = 0; i < num_dir; ++i) {
				
				snprintf(text, sizeof("u_dir_lights[%d].light_color"), "u_dir_lights[%d].light_color", i);
				light_struct_id = get_program()->get_uniform_position(text);
				
				get_program()->set_uniform_value(light_struct_id, 
					EDK3::T_FLOAT_3, 
					mat->dir_lights()[i].light_color_);

				printf("%s , %d\n", text, mat->dir_lights()[i].light_color_);
			 
			}
			 
			for (int i = 0; i < num_dir; ++i) {

				snprintf(text, sizeof("u_dir_lights[%d].light_force"), "u_dir_lights[%d].light_force", i);
				light_struct_id = get_program()->get_uniform_position(text);
				
				get_program()->set_uniform_value(light_struct_id, 
					EDK3::T_FLOAT_1, 
					&mat->dir_lights()[i].light_strength_);

				printf("%s , %d\n", text, mat->dir_lights()[i].light_strength_);
			 
			}
		
		}

		if (mat->point_lights()) {
			char text[1000];
			int num_dir = mat->num_point_lights();
			int light_struct_id;
			for (int i = 0; i < num_dir; ++i) {

				snprintf(text, sizeof("u_point_lights[%d].position"), "u_point_lights[%d].position", i);
				light_struct_id = get_program()->get_uniform_position(text);

				get_program()->set_uniform_value(light_struct_id, 
					EDK3::T_FLOAT_3, 
					mat->point_lights()[i].light_pos_);

			}

			for (int i = 0; i < num_dir; ++i) {

				snprintf(text, sizeof("u_point_lights[%d].ambient"), "u_point_lights[%d].ambient", i);
				light_struct_id = get_program()->get_uniform_position(text);
				
				get_program()->set_uniform_value(light_struct_id, 
					EDK3::T_FLOAT_3, 
					mat->point_lights()[i].ambient_light_);
			
			}

			for (int i = 0; i < num_dir; ++i) {

				snprintf(text, sizeof("u_point_lights[%d].diffuse"), "u_point_lights[%d].diffuse", i);
				light_struct_id = get_program()->get_uniform_position(text);
				
				get_program()->set_uniform_value(light_struct_id, 
					EDK3::T_FLOAT_3, 
					mat->point_lights()[i].diffuse_light_);
			
			}
			
			for (int i = 0; i < num_dir; ++i) {
				
				snprintf(text, sizeof("u_point_lights[%d].specular"), "u_point_lights[%d].specular", i);
				light_struct_id = get_program()->get_uniform_position(text);
				
				get_program()->set_uniform_value(light_struct_id, 
					EDK3::T_FLOAT_3, 
					mat->point_lights()[i].specular_light_);
			
			}
			 
			for (int i = 0; i < num_dir; ++i) {
				
				snprintf(text, sizeof("u_point_lights[%d].light_color"), "u_point_lights[%d].light_color", i);
				light_struct_id = get_program()->get_uniform_position(text);
				
				get_program()->set_uniform_value(light_struct_id, 
					EDK3::T_FLOAT_3, 
					mat->point_lights()[i].light_color_);

			}
			 
			for (int i = 0; i < num_dir; ++i) {
				
				snprintf(text, sizeof("u_point_lights[%d].light_force"), "u_point_lights[%d].light_force", i);
				light_struct_id = get_program()->get_uniform_position(text);
				
				get_program()->set_uniform_value(light_struct_id, 
					EDK3::T_FLOAT_1, 
					&mat->point_lights()[i].light_strength_);
			 
			}
 
			for (int i = 0; i < num_dir; ++i) {
				
				snprintf(text, sizeof("u_point_lights[%d].linear"), "u_point_lights[%d].linear", i);
				light_struct_id = get_program()->get_uniform_position(text);
				
				get_program()->set_uniform_value(light_struct_id, 
					EDK3::T_FLOAT_1, 
					&mat->point_lights()[i].linear_light_);

			}
 
			for (int i = 0; i < num_dir; ++i) {

				snprintf(text, sizeof("u_point_lights[%d].constant"), "u_point_lights[%d].constant", i);
				light_struct_id = get_program()->get_uniform_position(text);
				
				get_program()->set_uniform_value(light_struct_id, 
					EDK3::T_FLOAT_1, 
					&mat->point_lights()[i].constant_);
			 
			}
			 
			for (int i = 0; i < num_dir; ++i) {
				
				snprintf(text, sizeof("u_point_lights[%d].quadratic"), "u_point_lights[%d].quadratic", i);
				light_struct_id = get_program()->get_uniform_position(text);
				
				get_program()->set_uniform_value(light_struct_id, 
					EDK3::T_FLOAT_1, 
					&mat->point_lights()[i].quadratic_);
			
			}
		}

		if (mat->spot_lights()) {

			char text[1000];

			int num_dir = mat->num_spot_lights();
			int light_struct_id;

			for (int i = 0; i < num_dir; ++i) {

				snprintf(text, sizeof("u_spot_lights[%d].position"), "u_spot_lights[%d].position", i);
				light_struct_id = get_program()->get_uniform_position(text);
				
				get_program()->set_uniform_value(light_struct_id,
					EDK3::T_FLOAT_3,
					mat->spot_lights()[i].light_pos_);

				printf("%s , %d\n", text, mat->spot_lights()[i].light_pos_);
			
			}
			
			for (int i = 0; i < num_dir; ++i) {

				snprintf(text, sizeof("u_spot_lights[%d].direction"), "u_spot_lights[%d].direction", i);
				light_struct_id = get_program()->get_uniform_position(text);
			   
				get_program()->set_uniform_value(light_struct_id, 
				   EDK3::T_FLOAT_3, 
				   mat->spot_lights()[i].light_dir_);
			
			}
			
			for (int i = 0; i < num_dir; ++i) {
				
				snprintf(text, sizeof("u_spot_lights[%d].ambient"), "u_spot_lights[%d].ambient", i);
				light_struct_id = get_program()->get_uniform_position(text);
				
				get_program()->set_uniform_value(light_struct_id, 
					EDK3::T_FLOAT_3, 
					mat->spot_lights()[i].ambient_light_);
			
			}
			 
			for (int i = 0; i < num_dir; ++i) {

				snprintf(text, sizeof("u_spot_lights[%d].diffuse"), "u_spot_lights[%d].diffuse", i);
				light_struct_id = get_program()->get_uniform_position(text);
			   
				get_program()->set_uniform_value(light_struct_id, 
					EDK3::T_FLOAT_3, 
					mat->spot_lights()[i].diffuse_light_);
			 
			}
			 
			for (int i = 0; i < num_dir; ++i) {
			   
				snprintf(text, sizeof("u_spot_lights[%d].specular"), "u_spot_lights[%d].specular", i);
				light_struct_id = get_program()->get_uniform_position(text);
			   
				get_program()->set_uniform_value(light_struct_id, 
					EDK3::T_FLOAT_3, 
					mat->spot_lights()[i].specular_light_);
			 
			}
			  
			for (int i = 0; i < num_dir; ++i) {
			   
				snprintf(text, sizeof("u_spot_lights[%d].light_color"), "u_spot_lights[%d].light_color", i);
				light_struct_id = get_program()->get_uniform_position(text);
			   
				get_program()->set_uniform_value(light_struct_id, 
					EDK3::T_FLOAT_3, 
					mat->spot_lights()[i].light_color_);
			
			}
			  
			for (int i = 0; i < num_dir; ++i) {

				snprintf(text, sizeof("u_spot_lights[%d].light_force"), "u_spot_lights[%d].light_force", i);
				light_struct_id = get_program()->get_uniform_position(text);

				get_program()->set_uniform_value(light_struct_id, 
				   EDK3::T_FLOAT_1, 
				   &mat->spot_lights()[i].light_strength_);
			   
			}
			 
			for (int i = 0; i < num_dir; ++i) {

				snprintf(text, sizeof("u_spot_lights[%d].linear"), "u_spot_lights[%d].linear", i);
				light_struct_id = get_program()->get_uniform_position(text);

				get_program()->set_uniform_value(light_struct_id, 
				   EDK3::T_FLOAT_1, 
				   &mat->spot_lights()[i].linear_light_);
			   
			}
			 
			for (int i = 0; i < num_dir; ++i) {
			   
				snprintf(text, sizeof("u_spot_lights[%d].constant"), "u_spot_lights[%d].constant", i);
				light_struct_id = get_program()->get_uniform_position(text);
			   
				get_program()->set_uniform_value(light_struct_id, 
				   EDK3::T_FLOAT_1, 
				   &mat->spot_lights()[i].constant_);
			   
			}
			 
			for (int i = 0; i < num_dir; ++i) {
				
				snprintf(text, sizeof("u_spot_lights[%d].quadratic"), "u_spot_lights[%d].quadratic", i);
				light_struct_id = get_program()->get_uniform_position(text);
			   
				get_program()->set_uniform_value(light_struct_id, 
				   EDK3::T_FLOAT_1, 
				   &mat->spot_lights()[i].quadratic_);
			   
			}
			
			for (int i = 0; i < num_dir; ++i) {
			   
				snprintf(text, sizeof("u_spot_lights[%d].angle"), "u_spot_lights[%d].angle", i);
				light_struct_id = get_program()->get_uniform_position(text);
				
				get_program()->set_uniform_value(light_struct_id, 
					EDK3::T_FLOAT_1, 
					&mat->spot_lights()[i].angle_);
			   
			}
			
			for (int i = 0; i < num_dir; ++i) {
			   
				snprintf(text, sizeof("u_spot_lights[%d].external_angle"), "u_spot_lights[%d].external_angle", i);
				light_struct_id = get_program()->get_uniform_position(text);
			   
				get_program()->set_uniform_value(light_struct_id, 
					EDK3::T_FLOAT_1, 
					&mat->spot_lights()[i].ext_angle_);
			   
			}
		}

	}

	//Tremendo si funciona a la primera
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

