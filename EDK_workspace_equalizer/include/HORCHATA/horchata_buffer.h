#ifndef INCLUDE_HORCHATA_BUFFER_H_
#define INCLUDE_HORCHATA_DEV_BUFFER_H_ 1

#include <EDK3/dev/buffer.h>
#include <EDK3/dev/opengl.h>

namespace HORCHATA {

	class Buffer : public EDK3::dev::Buffer {

	public:

		Buffer();

		virtual void init(unsigned int size) override;
		virtual void bind(const Target t) const override;
		virtual unsigned int size() const override;
		virtual void uploadData(
			const void *data,
			unsigned int size,
			unsigned int offset = 0) override;
		virtual void release() override;
		
	private:
		GLuint size_;
		GLuint buffer_id_;
		const GLuint buffer_initial_id_ = std::numeric_limits<GLint>::max();

	};

}



#endif