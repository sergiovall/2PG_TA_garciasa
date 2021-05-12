#pragma once

#include <EDK3/ref_ptr.h>
#include <ESAT_extra/imgui.h>
#include <EDK3/node.h>
#include <EDK3/dev/buffer.h>
#include <EDK3/dev/gpumanager.h>

class DirLight : public EDK3::Node {

public:
	DirLight();
	~DirLight();

	void showImguiWindow(int i);

	void initDirLight(
		float dir[3] = { 0 },
		float ambient_light[3] = { 0 },
		float diff [3] = { 0 },
		float specular [3] = { 0 },
		float color [3] = { 0 },
		float light_force = 0.0f);

	float dir_[4];
	float ambient_light_[4];
	float diffuse_light_[4];
	float specular_light_[4];
	float light_color_[4];
	float light_strength_;
	

};