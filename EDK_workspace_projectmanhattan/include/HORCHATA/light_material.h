#pragma once

#include <EDK3/ref_ptr.h>
#include <EDK3/material.h>
#include <EDK3/materialsettings.h>
#include <EDK3/matdiffusetexture.h>
#include <EDK3/texture.h>
#include <EDK3/dev/program.h>
#include <HORCHATA/dir_light.h>
#include <HORCHATA/point_light.h>
#include <HORCHATA/spot_light.h>

class Program;

class LightMaterial : public EDK3::MatDiffuseTexture {


	LightMaterial();
	virtual bool enable(const EDK3::MaterialSettings *mat_settings) const override;
	virtual void setupCamera(const float projecton[16], const float view[16]) const override;
	virtual void setupModel(const float m[16]) const;

	virtual unsigned int num_attributes_required() const override;
	virtual EDK3::Attribute attribute_at_index(
		const unsigned int attrib_idx) const override;
	virtual EDK3::Type attribute_type_at_index(
		const unsigned int attrib_index) const override;

	EDK3::dev::Program* get_program();
	const EDK3::dev::Program* get_program() const;
	//
	bool load_shaders(EDK3::ref_ptr<EDK3::dev::Shader> vertex_shader, EDK3::ref_ptr<EDK3::dev::Shader> fragment_shader);

	void set_program(EDK3::ref_ptr<EDK3::dev::Program> program);

	bool load_shaders_from_filepaths(const char* vertex_shader_path,
		const char* fragment_shader_path);

	class Settings : public EDK3::MaterialSettings {
	public:
		Settings() { for (int i = 0; i < 4; ++i) data_[i] = 1.0f; }
		void set_color(const float v[4]) { memcpy(data_, v, sizeof(data_)); }
		void set_color(float r, float g, float b, float a = 1.0f) {
			data_[0] = r; data_[1] = g; data_[2] = b; data_[3] = a;
		}
		
		void set_camera_position(float *v) {
			camera_position_ = v;
		}
		void set_fog(int* fog_) { activate_fog = fog_; }
		void set_fog_color(float* new_fog_color) { fog_color_ = new_fog_color; }
		void set_material_shine(float v) { shininesh_ = v; }

		void set_material_dirlights(DirLight* dir_light_array) {

			dir_lights_ = dir_light_array;

		}
		void set_num_dir_lights(int v) {
			num_dir_lights_ = v;
		}
		void set_material_pointlights(PointLight* point_light_array) {

			point_lights_ = point_light_array;

		}
		void set_num_point_lights(int v) {
			num_point_lights_ = v;
		}
		void set_material_spotlights(SpotLight* spot_light_array) {
			spot_lights_ = spot_light_array;
		}
		void set_num_spot_lights(int v) {
			num_spot_lights_ = v;
		}
		void imguiPanel(char *panel_name);

		DirLight* dir_lights() 
		{ 
			return dir_lights_; 
		}

		const int num_dir_lights() 
		{ 
			return num_dir_lights_; 
		}

		PointLight* point_lights() 
		{ 
			return point_lights_; 
		}
		
		const int num_point_lights() 
		{ 
			return num_point_lights_; 
		}
		
		SpotLight* spot_lights() 
		{ 
			return spot_lights_; 
		}
		
		const int num_spot_lights() 
		{ 
			return num_spot_lights_; 
		}

		const float *color() const { return data_; }
		const int *fog() const { return activate_fog; }
		const float *fog_color() const { return fog_color_; }
		const float *light_pos() const { return local_light_pos_; }
		const float *light_strenght() const { return local_light_strenght_; }
		const float *camera_position() const { return camera_position_; }
		const float material_shine() const { return shininesh_; }
		void set_texture(EDK3::Texture *tex) { texture_ = tex; textures_loaded_++; }
		EDK3::Texture* texture() { return texture_.get(); }
		const EDK3::Texture* texture() const { return texture_.get(); }
		float* get_data() { return data_; }
		float shininesh_ = 5.0f;
	protected:
		virtual ~Settings() {}
	private:
		Settings(const Settings&);
		Settings& operator=(const Settings&);
		float data_[4];

		float *local_light_pos_;
		float *local_light_strenght_;
		float *camera_position_;
		float *fog_color_;
		EDK3::ref_ptr<EDK3::Texture> texture_;
		int *activate_fog;
		DirLight* dir_lights_;
		PointLight* point_lights_;
		SpotLight* spot_lights_;
		int num_dir_lights_;
		int num_point_lights_;
		int num_spot_lights_;
	};


	static int textures_loaded_;

protected:
	virtual ~LightMaterial() {}
private:
	EDK3::ref_ptr<EDK3::dev::Program> program_;
	LightMaterial(const LightMaterial&);
	LightMaterial& operator=(const LightMaterial &);
};