#pragma once

#include <EDK3/ref_ptr.h>
#include <ESAT_extra/imgui.h>
#include <EDK3/node.h>
#include <EDK3/dev/buffer.h>
#include <EDK3/dev/gpumanager.h>

class SpotLight : public EDK3::Node {

public:
	SpotLight();
	~SpotLight();

	void showImguiWindow(int i);

	void initSpotLight(
		float pos[3] = { 0 },
		float dir[3] = {0},
		float ambient_light[3] = { 0 },
		float diff[3] = { 0 },
		float specular[3] = { 0 },
		float color[3] = { 0 },
		float light_force = 0.0f,
		float linear = 0.0f,
		float constant = 0.0f,
		float quadratic = 0.0f,
		float angle = 0.0f,
		float external_angle = 0.0f);

	float light_pos_[4];
	float light_dir_[4];
	float ambient_light_[4];
	float diffuse_light_[4];
	float specular_light_[4];
	float light_color_[4];
	float light_strength_;
	float linear_light_;
	float constant_;
	float quadratic_;
	float angle_;
	float ext_angle_;

};