#ifndef __HORCHATA_PROGRAM_H__
#define __HORCHATA_PROGRAM_H__ 1

#include <EDK3/dev/program.h>
#include <EDK3/dev/opengl.h>
#include <HORCHATA/horchata_shader.h>


namespace HORCHATA {

	class Program : public EDK3::dev::Program {


	public:

		Program();
		~Program();

		virtual void attach(EDK3::dev::Shader *shader_id) override;

		virtual bool link(EDK3::scoped_array<char> *link_log = 0L) override;

		virtual void use() const override;

		virtual int get_attrib_location(const char *name) const override;

		virtual int get_uniform_position(const char *name) const override;

		virtual void set_uniform_value(const int uniform_pos, 
			const EDK3::Type uniform_type, 
			const float *value) const override;

		virtual void set_uniform_value(const int uniform_pos, 
			const EDK3::Type uniform_type, 
			const int *value) const override;

		virtual void set_uniform_value(const int uniform_pos, 
			const EDK3::Type uniform_type, 
			const unsigned int *value) const override;

		virtual unsigned int internal_id() const override;

	private:

		GLuint program_id;

	};

}


#endif