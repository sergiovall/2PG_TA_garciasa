#include <ESAT/window.h>
#include <ESAT/input.h>
#include <ESAT/draw.h>
#include <ESAT/time.h>

#include <EDK3/geometry.h>
#include <EDK3/camera.h>
#include <EDK3/drawable.h>
#include <EDK3/matdiffuse.h>
#include <EDK3/dev/gpumanager.h>


double previus_time;

struct GameState {
	EDK3::ref_ptr<EDK3::Camera> camera;
	EDK3::ref_ptr<EDK3::Node> root;
	EDK3::ref_ptr<EDK3::Node> merc_root;
	EDK3::ref_ptr<EDK3::Node> earth_root;

};

void prepare(GameState *state) {
	EDK3::dev::GPUManager::CheckGLError("Prepare Start");
	
	// Create cube
	EDK3::ref_ptr<EDK3::Geometry> cube_geometry;
	EDK3::CreateCube(&cube_geometry, 1.0f, true, false);
	
	// Material
	EDK3::ref_ptr<EDK3::MatDiffuse> diffuse_material;
	EDK3::ref_ptr<EDK3::MatDiffuse::Settings> diffuse_material_settings;

	diffuse_material.alloc();
	diffuse_material_settings.alloc();
	
	// Nodes
	EDK3::Node *root = state->root.alloc();
	EDK3::Node *merc_root = state->merc_root.alloc();
	EDK3::Node *earth_root = state->earth_root.alloc();

	// Create a Drawable Node (Geometry + Material + Settings)
	EDK3::ref_ptr<EDK3::Drawable> sun;	
	EDK3::ref_ptr<EDK3::Drawable> mercury;	
	EDK3::ref_ptr<EDK3::Drawable> earth;	


	// Graphic
	sun.alloc();
	sun->set_geometry(cube_geometry.get());
	sun->set_material(diffuse_material.get());
	sun->set_material_settings(diffuse_material_settings.get());
	mercury.alloc();
	mercury->set_geometry(cube_geometry.get());
	mercury->set_material(diffuse_material.get());
	mercury->set_material_settings(diffuse_material_settings.get());
	earth.alloc();
	earth->set_geometry(cube_geometry.get());
	earth->set_material(diffuse_material.get());
	earth->set_material_settings(diffuse_material_settings.get());

	// Transform
	sun->set_position(0.0f, 0.0f, -3.0f);
	sun->set_scale(0.6f, 0.6f, 0.6f);
	root->addChild(sun.get());
	mercury->set_position(1.5f, 0.0f, 0.0f);
	mercury->set_scale(0.2f, 0.2f, 0.2f);
	earth->set_position(3.8f, 0.0f, 0.0f);
	earth->set_scale(0.35f, 0.35f, 0.35f);
	sun->addChild(merc_root);
	sun->addChild(earth_root);
	merc_root->addChild(mercury.get());
	earth_root->addChild(earth.get());

	// Color 
	float green_color[] = { 255.0f / 255.0f, 40.0f / 255.0f, 162.0f / 255.0f, 1.0f };
	diffuse_material_settings->set_color(green_color);

	// Create a Camera
	state->camera.alloc();
	float pos[] = { 0.0f, 0.0f, 1.5f };
	float view[] = { 0.0f, 0.0f, -1.0f };
	state->camera->set_position(pos);
	state->camera->set_view_direction(view);
	state->camera->setupPerspective(70, 1280.0f / 720.0f, 1.0f, 1500.0f);
	state->camera->set_clear_color(0.99f, 0.99f, 0.99f, 1.0f);
	EDK3::dev::GPUManager::CheckGLError("Prepare END");
}

void render_function(GameState *state) {
	
	// Update
	state->merc_root->set_rotation_y(6.0f * ESAT::Time() / 300.0f);
	state->earth_root->set_rotation_y(3.5f * ESAT::Time() / 300.0f);
	// Se me ocurre crear un root y hacerlo hijo del sol y así etc

	// For Every frame... determine what's visible:
	state->camera->doCull(state->root.get());
	
	// Render
	EDK3::dev::GPUManager::CheckGLError("begin Render-->");
	state->camera->doRender();
	EDK3::dev::GPUManager::CheckGLError("end Render-->");
}

void camera_funcs(GameState *state) {

	if (ESAT::IsKeyPressed('W')) {
		float pos[3]{ state->camera->position()[0],state->camera->position()[1],state->camera->position()[2] - 0.1};
		state->camera->set_position(pos);
	}
	if (ESAT::IsKeyPressed('S')) {
		float pos[3]{ state->camera->position()[0],state->camera->position()[1],state->camera->position()[2] + 0.1 };
		state->camera->set_position(pos);
	}
	if (ESAT::IsKeyPressed('A')) {
		float pos[3]{ state->camera->position()[0] + 0.1,state->camera->position()[1],state->camera->position()[2] };
		state->camera->set_position(pos);
	}
	if (ESAT::IsKeyPressed('D')) {
		float pos[3]{ state->camera->position()[0] - 0.1,state->camera->position()[1],state->camera->position()[2] };
		state->camera->set_position(pos);
	}

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

		camera_funcs(&state);
		render_function(&state);	
		ESAT::WindowFrame();
	}

	return 0;
}
