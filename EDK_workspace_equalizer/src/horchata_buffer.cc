#include <HORCHATA/horchata_buffer.h>
#include <EDK3/dev/gpumanager.h>

HORCHATA::Buffer::Buffer() {

	buffer_id_ = buffer_initial_id_;

}

void HORCHATA::Buffer::init(unsigned int size) {

	release();

	size_ = size;
	glGenBuffers(1, &buffer_id_);

	bind(kTarget_Elements);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);

}

void HORCHATA::Buffer::bind(const Target t) const {

	switch (t)
	{
	case kTarget_Elements:
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id_);
		break;

	case kTarget_Vertex_Data:
		glBindBuffer(GL_ARRAY_BUFFER, buffer_id_);
		break;
	default:
		break;
	}

}

unsigned int HORCHATA::Buffer::size() const {

	return size_;

}

void HORCHATA::Buffer::uploadData(const void * data, unsigned int size, unsigned int offset) {

	bind(kTarget_Vertex_Data);

	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);

}

void HORCHATA::Buffer::release() {
	if (buffer_id_ != buffer_initial_id_) {

		glDeleteBuffers(1, &buffer_id_);
		size_ = 0;

	}
}