#pragma once
// ----------------------------------------------------------------------------
// Copyright (C) 2017 Lucas Gonzalez
// Test Material Implementation
// ----------------------------------------------------------------------------

#include <EDK3/matcustom.h>

#include <EDK3/dev/shader.h>
#include <EDK3/dev/gpumanager.h>
#include <EDK3/dev/program.h>



class MyCustomMaterial : public EDK3::MatCustom {
public:

	MyCustomMaterial();

	virtual bool load_shaders(EDK3::ref_ptr<EDK3::dev::Shader> vertex_shader, EDK3::ref_ptr<EDK3::dev::Shader> fragment_shader) override;

	virtual bool enable(const EDK3::MaterialSettings*) const override;

protected:
	virtual ~MyCustomMaterial() {};

 };


