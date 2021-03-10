#include <YO/triangle.h>
#include <EDK3/dev/gpumanager.h>


bool Triangle::bindAttribute(const EDK3::Attribute a, unsigned int where_to_bind_attribute) const
{
	return false;
}

void Triangle::render() const
{

}

void Triangle::generate()
{

	EDK3::dev::GPUManager::Instance()->newBuffer(&vertex_buffer);

	float vertex_array[]{ 0.0f,0.5f, 0.0f,
						0.5f,-0.5f,0.0f,
						-0.5f,-0.5f,0.0f };

	float normal_array[]{ 0.0f,0.0f,1.0f,
						0.0f,0.0f,1.0f,
						0.0f,0.0f,1.0f };

	vertex_buffer->init(sizeof(vertex_array)*2);
	vertex_buffer->uploadData(vertex_array, sizeof(vertex_array), 0);
	vertex_buffer->uploadData(normal_array, sizeof(normal_array), sizeof(normal_array));

	EDK3::dev::GPUManager::Instance()->newBuffer(&index_buffer);

	unsigned int index_array[]{ 0 , 1, 2 };

	index_buffer->init(sizeof(index_array));
	index_buffer->uploadData(index_array, sizeof(index_array), 0);

}
