#include <HORCHATA/point_light.h>
#include <string>

PointLight::PointLight()
{

	light_strength_ = 0.0f;
	linear_light_ = 0.0f;
	constant_ = 0.0f;
	quadratic_ = 0.0f;

	for (int i = 0; i < 4; i++) {

		light_pos_[i] = 0.0f;
		ambient_light_[i] = 0.0f;
		diffuse_light_[i] = 0.0f;
		specular_light_[i] = 0.0f;
		light_color_[i] = 0.0f;

	}

}

PointLight::~PointLight()
{
}

void PointLight::showImguiWindow(int i)
{

	std::string text = "Point Light " + std::to_string(i);

	if (ImGui::Begin(text.c_str())) {

		ImGui::SliderFloat("Lposition X", &light_pos_[0], -10000.0f, 10000.0f);
		ImGui::SliderFloat("Lposition Y", &light_pos_[1], -10000.0f, 10000.0f);
		ImGui::SliderFloat("Lposition Z", &light_pos_[2], -10000.0f, 10000.0f);

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
		ImGui::SliderFloat("LinearL", &linear_light_, 0.0f, 15.0f);
		ImGui::SliderFloat("Constant", &constant_, 0.0f, 15.0f);
		ImGui::SliderFloat("Quadratic_", &quadratic_, 0.0f, 15.0f);

		ImGui::End();

	}

}


void PointLight::initPointLight(float pos[3], float ambient_light[3], float diff[3], float specular[3], float color[3], float light_force, float linear, float constant, float quadratic)
{

	light_strength_ = light_force;
	linear_light_ = linear;
	constant_ = constant;
	quadratic_ = quadratic;

	for (int i = 0; i < 3; i++) {

		light_pos_[i] = pos[i];
		ambient_light_[i] = ambient_light[i];
		diffuse_light_[i] = diff[i];
		specular_light_[i] = specular[i];
		light_color_[i] = color[i];

	}

}

void PointLight::setPosition(float pos[3])
{

	for (int i = 0; i < 3; i++) {

		light_pos_[i] = pos[i];

	}

}
