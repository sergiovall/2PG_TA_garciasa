#include <YO/triangle.h>
#include <EDK3/dev/gpumanager.h>


bool Triangle::bindAttribute(const EDK3::Attribute a, unsigned int where_to_bind_attribute) const
{
	
	switch (a) {
	case EDK3::A_POSITION:
	EDK3::dev::GPUManager::Instance()->enableVertexAttribute(vertex_buffer.get(), where_to_bind_attribute, EDK3::T_FLOAT_3, false);
	return true;
	break;
	case EDK3::A_NORMAL:
	EDK3::dev::GPUManager::Instance()->enableVertexAttribute(vertex_buffer.get(), where_to_bind_attribute, EDK3::T_FLOAT_3, false);
	return true;
	break;
	}

}

void Triangle::render() const
{
	EDK3::dev::GPUManager::Instance()->drawElements(EDK3::dev::GPUManager::DrawMode::kDrawMode_Triangles, 3, index_buffer.get(), EDK3::T_UINT_1);
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

	unsigned int index_array[]{ 2 , 1, 0 };

	index_buffer->init(sizeof(index_array));
	index_buffer->uploadData(index_array, sizeof(index_array), 0);

}
