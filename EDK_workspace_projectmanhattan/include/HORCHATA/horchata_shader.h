#ifndef INCLUDE_HORCHATA_SHADER_H_
#define INCLUDE_HORCHATA_DEV_SHADER_H_ 1

#include <EDK3/dev/shader.h>
#include <EDK3/dev/opengl.h>

namespace HORCHATA {

	class Shader : public EDK3::dev::Shader {

	public:

		virtual void loadSource(
			const Type shader_type,
			const char *source,
			const unsigned int source_size) override;

		virtual bool compile(EDK3::scoped_array<char> *output_log = NULL) override;

		virtual bool is_compiled() const override;

		virtual const Type type() const override;

		virtual unsigned int internal_id() const override;

	protected:
		
		Shader(){}
		virtual ~Shader(){}
	
	private:

		GLuint shader_id;


	};

}



#endif