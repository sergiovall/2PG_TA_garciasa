#include <ESAT/window.h>
#include <ESAT/input.h>
#include <ESAT/draw.h>
#include <ESAT/time.h>

#include <EDK3/geometry.h>
#include <EDK3/camera.h>
#include <EDK3/drawable.h>
#include <EDK3/matdiffuse.h>
#include <EDK3/dev/gpumanager.h>

#include <ESAT_extra/soloud/soloud.h>
#include <ESAT_extra/soloud/soloud_wav.h>

#include <HORCHATA/horchata_gpu_manager.h>

double previus_time;
const int kNumNodes = 32;

struct GameState {
	EDK3::ref_ptr<EDK3::Camera> camera;
	EDK3::ref_ptr<EDK3::Node> root[kNumNodes];
	EDK3::ref_ptr<EDK3::Node> scene_root;
	SoLoud::Soloud soloud;
};

void prepare(GameState *state) {
	EDK3::dev::GPUManager::CheckGLError("Prepare Start");
	
	// Create cube
	EDK3::ref_ptr<EDK3::Geometry> cube_geometry;
	EDK3::CreateCube(&cube_geometry, 1.0f, true, false);
	
	// Material
	EDK3::ref_ptr<EDK3::MatDiffuse> diffuse_material;
	EDK3::ref_ptr<EDK3::MatDiffuse::Settings> diffuse_material_settings[kNumNodes];

	diffuse_material.alloc();
	for (int i = 0; i < kNumNodes; i++) {
		diffuse_material_settings[i].alloc();
	}
	//diffuse_material_settings.alloc();
	
	// Nodes
	//EDK3::Node *root = state->root.alloc();

	EDK3::Node *root[kNumNodes];
	EDK3::Node *scene_root = state->scene_root.alloc();

	for (int i = 0; i < kNumNodes; i++) {
		root[i] = state->root[i].alloc();
		scene_root->addChild(root[i]);
		root[i]->set_position((-kNumNodes/2+i)*0.2f, 0.0f, 0.0f);
	}

	

	// Create a Drawable Node (Geometry + Material + Settings)
	EDK3::ref_ptr<EDK3::Drawable> drawable[kNumNodes];

	// Material
	//diffuse_material_settings.alloc();

	// Graphic

	for (int i = 0; i < kNumNodes; i++) {

		drawable[i].alloc();
		drawable[i]->set_geometry(cube_geometry.get());
		drawable[i]->set_material(diffuse_material.get());
		drawable[i]->set_material_settings(diffuse_material_settings[i].get());

	}



	// Transform
	for (int i = 0; i < kNumNodes; i++) {

		drawable[i]->set_position(0.0f, 0.0f, 0.0f);
		drawable[i]->set_scale(0.1f, 0.1f, 0.1f);
		root[i]->addChild(drawable[i].get());

	}

	// Color 
	for (int i = 0; i < kNumNodes; i++)
	{
		float color[] = { 255.0f / 255.0f, i * 256 / kNumNodes /2.0f / 255.0f, i*256/kNumNodes / 255.0f, 1.0f };

		diffuse_material_settings[i]->set_color(color);
	}
	//diffuse_material_settings->set_color(green_color);

	// Create a Camera
	state->camera.alloc();
	float pos[] = { 0.0f, 0.0f, kNumNodes/7.0f };
	float view[] = { 0.0f, 0.0f, -1.0f };
	state->camera->set_position(pos);
	state->camera->set_view_direction(view);
	state->camera->setupPerspective(60, 1280.0f / 720.0f, 1.0f, 1500.0f);
	state->camera->set_clear_color(0.0f, 0.0f, 0.0f, 1.0f);
	EDK3::dev::GPUManager::CheckGLError("Prepare END");
}

void update_function(GameState *state) {

	// Sound data
	float* waveData = state->soloud.calcFFT();

	// Rotation
	//state->root->set_rotation_y(5.0f * ESAT::Time() / 300.0f);

	// Scale
	
	float transitionForce = 0.4f;
	for (int i = 0; i < kNumNodes; i++) {

		float waveDataAvg = 0.0f;
		for (int j = 0; j < 256/kNumNodes; j++) {
			waveDataAvg += waveData[i * 256 / kNumNodes + j];
		}
		waveDataAvg /= 256 / kNumNodes;
		float newScale = 5.0f + waveDataAvg * 10.0f;
		float scale = newScale * transitionForce + state->root[i]->scale()[0] * (1.0f - transitionForce);
		state->root[i]->set_scale(1, scale, 1);

	}
	

}

void render_function(GameState *state) {
	
	

	// For Every frame... determine what's visible:
	state->camera->doCull(state->scene_root.get());
	
	// Render
	EDK3::dev::GPUManager::CheckGLError("begin Render-->");
	state->camera->doRender();
	EDK3::dev::GPUManager::CheckGLError("end Render-->");
}

int ESAT::main(int argc, char **argv) {
	
	// State
	GameState state;
	HORCHATA::GPUManager *gpu_manager = new HORCHATA::GPUManager();
	EDK3::dev::GPUManager::ReplaceGPUManagerImplementation(gpu_manager);
	ESAT::WindowInit(1280, 720);
	ESAT::DrawSetTextFont("test.ttf");
	ESAT::DrawSetTextSize(18);
	ESAT::DrawSetFillColor(253, 255, 255, 128);
	prepare(&state);


	// Init soloud and play sound	
	SoLoud::Wav sample;

	state.soloud.init(SoLoud::Soloud::ENABLE_VISUALIZATION);
	sample.load("test.ogg");
	SoLoud::handle handle = state.soloud.play(sample);
	//state.soloud.setVolume(handle, 0.1f);

	
	// Main loop
	while (ESAT::WindowIsOpened() && !ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape)) {
		
		double currentTime = RawTime();
		double delta_time = (currentTime - previus_time) / 1000.0f;
		previus_time = currentTime;
		
		update_function(&state);
		render_function(&state);
		ESAT::WindowFrame();
	}

	return 0;
}
