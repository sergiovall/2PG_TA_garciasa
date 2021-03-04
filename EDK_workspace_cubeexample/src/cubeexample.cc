#include <ESAT/window.h>
#include <ESAT/input.h>
#include <ESAT/draw.h>
#include <ESAT/time.h>

#include <EDK3/geometry.h>
#include <EDK3/camera.h>
#include <EDK3/drawable.h>
#include <EDK3/matdiffuse.h>
#include <EDK3/dev/gpumanager.h>

#include "vector_3.h"


double previus_time;
float b_cube_angle = 0.0f;
float b_cube_distance = 2.5f;

struct GameState {
	EDK3::ref_ptr<EDK3::Camera> camera;
	EDK3::ref_ptr<EDK3::Node> root;
	EDK3::ref_ptr<EDK3::Node> a_root;
	EDK3::ref_ptr<EDK3::Node> b_root;
	EDK3::ref_ptr<EDK3::Node> c_root;

};

void prepare(GameState *state) {
	EDK3::dev::GPUManager::CheckGLError("Prepare Start");
	
	// Create cube
	EDK3::ref_ptr<EDK3::Geometry> cube_geometry;
	EDK3::CreateCube(&cube_geometry, 1.0f, true, false);
	
	// Material
	EDK3::ref_ptr<EDK3::MatDiffuse> diffuse_material;
	EDK3::ref_ptr<EDK3::MatDiffuse::Settings> a_diffuse_material_settings;
	EDK3::ref_ptr<EDK3::MatDiffuse::Settings> b_diffuse_material_settings;
	EDK3::ref_ptr<EDK3::MatDiffuse::Settings> c_diffuse_material_settings;

	diffuse_material.alloc();
	a_diffuse_material_settings.alloc();
	b_diffuse_material_settings.alloc();
	c_diffuse_material_settings.alloc();
	
	// Nodes
	EDK3::Node *root = state->root.alloc();
	EDK3::Node *a_root = state->a_root.alloc();
	EDK3::Node *b_root = state->b_root.alloc();
	EDK3::Node *c_root = state->c_root.alloc();


	// Create a Drawable Node (Geometry + Material + Settings)
	EDK3::ref_ptr<EDK3::Drawable> a_cube;	
	EDK3::ref_ptr<EDK3::Drawable> b_cube;	
	EDK3::ref_ptr<EDK3::Drawable> c_cube;	


	// Graphic
	a_cube.alloc();
	a_cube->set_geometry(cube_geometry.get());
	a_cube->set_material(diffuse_material.get());
	a_cube->set_material_settings(a_diffuse_material_settings.get());
	b_cube.alloc();
	b_cube->set_geometry(cube_geometry.get());
	b_cube->set_material(diffuse_material.get());
	b_cube->set_material_settings(b_diffuse_material_settings.get());
	c_cube.alloc();
	c_cube->set_geometry(cube_geometry.get());
	c_cube->set_material(diffuse_material.get());
	c_cube->set_material_settings(c_diffuse_material_settings.get());

	// Transform
	a_cube->set_position(0.0f, 0.0f, 0.0f);
	a_cube->set_scale(0.9f, 0.9f, 0.9f);
	b_cube->set_position(0.0f, 0.0f, 0.0f);
	b_cube->set_scale(0.25f, 0.25f, 0.25f);
	c_cube->set_position(0.0f, 0.0f, 0.0f);
	c_cube->set_scale(1.0f, 1.0f, 1.0f);
	state->root->addChild(a_root);
	state->root->addChild(b_root);
	state->root->addChild(c_root);
	state->a_root->addChild(a_cube.get());
	state->b_root->addChild(b_cube.get());
	state->c_root->addChild(c_cube.get());
	state->a_root->set_position(-5.0f,0.0f,0.0f);
	state->b_root->set_position(-2.5f,0.0f,0.0f);
	state->c_root->set_position(5.0f, 0.0f, 0.0f);

	// Color 
	float red_color[] = { 255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, 1.0f };
	float blue_color[] = { 0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, 1.0f };
	float yellow_color[] = { 255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f, 1.0f };
	a_diffuse_material_settings->set_color(red_color);
	b_diffuse_material_settings->set_color(blue_color);
	c_diffuse_material_settings->set_color(yellow_color);

	// Create a Camera
	state->camera.alloc();
	float pos[] = { 0.0f, 0.0f, 10.f };
	float view[] = { 0.0f, 0.0f, -2.0f };
	state->camera->set_position(pos);
	state->camera->set_view_direction(view);
	state->camera->setupPerspective(70, 1280.0f / 720.0f, 1.0f, 1500.0f);
	state->camera->set_clear_color(0.99f, 0.99f, 0.99f, 1.0f);
	EDK3::dev::GPUManager::CheckGLError("Prepare END");
}

float DegToRad(float angle) {
	return angle * 3.141592f / 180;
}

void b_behaviour(GameState *state) {
	Vector3 a_pos, b_pos, c_pos;
	const float *aux;
	aux = state->a_root->position();
	a_pos = Vector3({*(aux),*(aux+1),*(aux+2) });
	aux = state->b_root->position();
	b_pos = Vector3({ *(aux),*(aux + 1),*(aux + 2) });
	aux = state->c_root->position();
	c_pos = Vector3({ *(aux),*(aux + 1),*(aux + 2) });
	state->b_root->set_position(a_pos.x + b_cube_distance * cosf(DegToRad(b_cube_angle)),a_pos.y + b_cube_distance * sinf(DegToRad(b_cube_angle)),0.0f);
	b_cube_angle+=0.1f;

	float ac_distance = a_pos.Distance(a_pos, c_pos);
	float bc_distance = b_pos.Distance(b_pos, c_pos);

	float b_color = ac_distance - bc_distance;
	if (b_color < 0) {
		b_color = 0;
	}
	float cube_color[] = { 0.0f / 255.0f, 0.0f / 255.0f, b_color / 255.0f, 1.0f };
	printf("%d", b_color);
	

}

void render_function(GameState *state) {
	
	// Update
	// Se me ocurre crear un root y hacerlo hijo del sol y así etc

	// For Every frame... determine what's visible:
	state->camera->doCull(state->root.get());
	
	// Render
	EDK3::dev::GPUManager::CheckGLError("begin Render-->");
	state->camera->doRender();
	EDK3::dev::GPUManager::CheckGLError("end Render-->");
}

int ESAT::main(int argc, char **argv) {
	
	// State
	GameState state;
	ESAT::WindowInit(1280, 720);
	ESAT::DrawSetTextFont("test.ttf");
	ESAT::DrawSetTextSize(18);
	ESAT::DrawSetFillColor(253, 255, 255, 128);
	prepare(&state);
	
	// Main loop
	while (ESAT::WindowIsOpened() && !ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape)) {
		
		double currentTime = RawTime();
		double delta_time = (currentTime - previus_time) / 1000.0f;
		previus_time = currentTime;
		state.c_root->set_position((ESAT::MousePositionX()-1280/2)/60.0f, -(ESAT::MousePositionY()-720/2)/60.0f, 0.0f);
		b_behaviour(&state);

		render_function(&state);	
		ESAT::WindowFrame();
	}

	return 0;
}
