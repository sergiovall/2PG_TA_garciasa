#include <HORCHATA/dir_light.h>
#include <string>

DirLight::DirLight() {

	light_strength_ = 0.0f;

	for (int i = 0; i < 4;i++) {

		dir_[i] = 0.0f;
		ambient_light_[i] = 0.0f;
		diffuse_light_[i] = 0.0f;
		specular_light_[i] = 0.0f;
		light_color_[i] = 1.0f;

	}

}

DirLight::~DirLight(){}

void DirLight::showImguiWindow(int i) {
	
	std::string text = "Dir Light " + std::to_string(i);
	
	if (ImGui::Begin(text.c_str())) {

		ImGui::SliderFloat("directionL X", &dir_[0], -10000.0f, 10000.0f);
		ImGui::SliderFloat("directionL Y", &dir_[1], -10000.0f, 10000.0f);
		ImGui::SliderFloat("directionL Z", &dir_[2], -10000.0f, 10000.0f);

		ImGui::SliderFloat("light R", &light_color_[0], 0.0f, 1.0f);
		ImGui::SliderFloat("light G", &light_color_[1], 0.0f, 1.0f);
		ImGui::SliderFloat("light B", &light_color_[2], 0.0f, 1.0f);

		ImGui::SliderFloat("ambientL R", &ambient_light_[0], 0.0f, 1.0f);
		ImGui::SliderFloat("ambientL G", &ambient_light_[1], 0.0f, 1.0f);
		ImGui::SliderFloat("ambientL B", &ambient_light_[2], 0.0f, 1.0f);

		ImGui::SliderFloat("diffuseL R", &diffuse_light_[0], 0.0f, 1.0f);
		ImGui::SliderFloat("diffuseL G", &diffuse_light_[1], 0.0f, 1.0f);
		ImGui::SliderFloat("diffuseL B", &diffuse_light_[2], 0.0f, 1.0f);

		ImGui::SliderFloat("specularL R", &specular_light_[0], 0.0f, 1.0f);
		ImGui::SliderFloat("specularL G", &specular_light_[1], 0.0f, 1.0f);
		ImGui::SliderFloat("specularL B", &specular_light_[2], 0.0f, 1.0f);

		ImGui::SliderFloat("LStrength", &light_strength_, 0.0f, 15.0f);

		ImGui::End();

	}

}

void DirLight::initDirLight(float dir[3], float ambient_light[3], float diff[3], float specular[3], float color[3], float light_force)
{

	for (int i = 0; i < 3; i++) {

		dir_[i] = dir[i];
		ambient_light_[i] = ambient_light[i];
		diffuse_light_[i] = diff[i];
		specular_light_[i] = specular[i];
		light_color_[i] = color[i];

	}

	light_strength_ = light_force;

}


