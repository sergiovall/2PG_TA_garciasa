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

	protected:
		
		Shader(){}
		virtual ~Shader(){}
	
	private:

		Shader(const Shader&);
		Shader& operator=(const Shader&);

		GLuint shader;
		Type shader_type;


	};

}



#endif