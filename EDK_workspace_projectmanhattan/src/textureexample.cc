#include <ESAT/window.h>
#include <ESAT/input.h>
#include <ESAT/draw.h>
#include <ESAT/time.h>

#include <EDK3/geometry.h>
#include <EDK3/camera.h>
#include <EDK3/drawable.h>
#include <EDK3/texture.h>
#include <EDK3/matdiffusetexture.h>
#include <EDK3/dev/gpumanager.h>

using namespace ESAT;
using namespace EDK3;
using namespace EDK3::dev;

double previus_time;

struct GameState {
	ref_ptr<Camera> camera;
	ref_ptr<Node> root;
};

void prepare(GameState *state) {

	GPUManager::CheckGLError("Prepare Start");
	
	// Nodes
	Node* root = state->root.alloc();	
	ref_ptr<Drawable> drawable;
	drawable.alloc();
	root->addChild(drawable.get());

	// Load geometry
	scoped_array<ref_ptr<Geometry>> buildingGeometries;
	scoped_array<char> errorLog;
	LoadObj("../assets/Models/SM_Building_03.obj", &buildingGeometries, &errorLog);
	
	// Material
	ref_ptr<MatDiffuseTexture> diffuse_material;
	diffuse_material.alloc();

	// Texture
	ref_ptr<Texture> texture;
	Texture::Load("../assets/textures/T_building_03_Dif.png", &texture);
	texture->generateMipmaps();

	// Material Settings
	ref_ptr<MatDiffuseTexture::Settings> diffuse_material_settings;
	diffuse_material_settings.alloc();	
	diffuse_material_settings->set_color(1.0f, 1.0f, 1.0f);
	diffuse_material_settings->set_texture(texture.get());

	// Graphic
	drawable->set_geometry(buildingGeometries[0].get());
	drawable->set_material(diffuse_material.get());
	drawable->set_material_settings(diffuse_material_settings.get());

	// Create a Camera
	state->camera.alloc();
	float pos[] = { 0.0f, 1000.0f, 2200.0f };
	float view[] = { 0.0f, 0.0f, -1.0f };
	state->camera->set_position(pos);
	state->camera->set_view_direction(view);
	state->camera->setupPerspective(70, 1280.0f / 720.0f, 0.01f, 4000.0f);
	state->camera->set_clear_color(0.99f, 0.99f, 0.99f, 1.0f);

	GPUManager::CheckGLError("Prepare END");
}

void render_function(GameState *state) {
	
	// Update
	float rotationX = state->root->rotation_xyz()[0];
	rotationX = MousePositionY();
	state->root->set_rotation_x(rotationX);

	float rotationY = state->root->rotation_xyz()[1];	
	rotationY = MousePositionX();
	state->root->set_rotation_y(rotationY);
	
	// For Every frame... determine what's visible:
	state->camera->doCull(state->root.get());
	
	// Render
	GPUManager::CheckGLError("begin Render-->");
	state->camera->doRender();
	GPUManager::CheckGLError("end Render-->");
}

int ESAT::main(int argc, char **argv) {
	
	// State
	GameState state;
	WindowInit(1280, 720);
	DrawSetTextFont("test.ttf");
	DrawSetTextSize(18);
	DrawSetFillColor(253, 255, 255, 128);
	prepare(&state);
	
	// Main loop
	while (WindowIsOpened() && !IsSpecialKeyDown(kSpecialKey_Escape)) {
		
		double currentTime = RawTime();
		double delta_time = (currentTime - previus_time) / 1000.0f;
		previus_time = currentTime;
		
		render_function(&state);	
		WindowFrame();
	}

	return 0;
}