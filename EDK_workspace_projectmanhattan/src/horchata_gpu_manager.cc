#include <HORCHATA/horchata_gpu_manager.h>
#include <HORCHATA/horchata_buffer.h>
#include <HORCHATA/horchata_shader.h>
#include <HORCHATA/horchata_program.h>


HORCHATA::GPUManager::GPUManager() {}

HORCHATA::GPUManager::~GPUManager() {}

void HORCHATA::GPUManager::newBuffer(EDK3::ref_ptr<EDK3::dev::Buffer>* output) {

	output->allocT<Buffer>();

}

/*void HORCHATA::GPUManager::newShader(EDK3::ref_ptr<EDK3::dev::Shader>* output)
{
	
	output->allocT<Shader>();

}*/

void HORCHATA::GPUManager::newProgram(EDK3::ref_ptr<EDK3::dev::Program>* output)
{

	output->allocT<Program>();

}

void HORCHATA::GPUManager::enableVertexAttribute(const EDK3::dev::Buffer * buffer, 
	const unsigned int attribute_index, 
	const EDK3::Type type, 
	const bool normalized, 
	const unsigned int offset, 
	const unsigned int stride)
{
	GLenum data_type;
	GLint size;

	switch (type) {

	case EDK3::T_FLOAT_1:
		data_type = GL_FLOAT;
		size = 1;
		break;
	case EDK3::T_FLOAT_2:
		data_type = GL_FLOAT;
		size = 2;
		break;
	case EDK3::T_FLOAT_3:
		data_type = GL_FLOAT;
		size = 3;
		break;
	case EDK3::T_FLOAT_4:
		data_type = GL_FLOAT;
		size = 4;
		break;

	case EDK3::T_INT_1:
		data_type = GL_INT;
		size = 1;
		break;
	case EDK3::T_INT_2:
		data_type = GL_INT;
		size = 2;
		break;
	case EDK3::T_INT_3:
		data_type = GL_INT;
		size = 3;
		break;
	case EDK3::T_INT_4:
		data_type = GL_INT;
		size = 4;
		break;

	case EDK3::T_UINT_1:
		data_type = GL_UNSIGNED_INT;
		size = 1;
		break;
	case EDK3::T_UINT_2:
		data_type = GL_UNSIGNED_INT;
		size = 2;
		break;
	case EDK3::T_UINT_3:
		data_type = GL_UNSIGNED_INT;
		size = 3;
		break;
	case EDK3::T_UINT_4:
		data_type = GL_UNSIGNED_INT;
		size = 4;
		break;

	case EDK3::T_BYTE_1:
		data_type = GL_BYTE;
		size = 1;
		break;
	case EDK3::T_BYTE_2:
		data_type = GL_BYTE;
		size = 2;
		break;
	case EDK3::T_BYTE_3:
		data_type = GL_BYTE;
		size = 3;
		break;
	case EDK3::T_BYTE_4:
		data_type = GL_BYTE;
		size = 4;
		break;

	case EDK3::T_UBYTE_1:
		data_type = GL_UNSIGNED_BYTE;
		size = 1;
		break;
	case EDK3::T_UBYTE_2:
		data_type = GL_UNSIGNED_BYTE;
		size = 2;
		break;
	case EDK3::T_UBYTE_3:
		data_type = GL_UNSIGNED_BYTE;
		size = 3;
		break;
	case EDK3::T_UBYTE_4:
		data_type = GL_UNSIGNED_BYTE;
		size = 4;
		break;

	case EDK3::T_SHORT_1:
		data_type = GL_SHORT;
		size = 1;
		break;
	case EDK3::T_SHORT_2:
		data_type = GL_SHORT;
		size = 2;
		break;
	case EDK3::T_SHORT_3:
		data_type = GL_SHORT;
		size = 3;
		break;
	case EDK3::T_SHORT_4:
		data_type = GL_SHORT;
		size = 4;
		break;

	case EDK3::T_USHORT_1:
		data_type = GL_UNSIGNED_SHORT;
		size = 1;
		break;
	case EDK3::T_USHORT_2:
		data_type = GL_UNSIGNED_SHORT;
		size = 1;
		break;
	case EDK3::T_USHORT_3:
		data_type = GL_UNSIGNED_SHORT;
		size = 1;
		break;
	case EDK3::T_USHORT_4:
		data_type = GL_UNSIGNED_SHORT;
		size = 1;
		break;

	case EDK3::T_DOUBLE_1:
		data_type = GL_DOUBLE;
		size = 1;
		break;
	case EDK3::T_DOUBLE_2:
		data_type = GL_DOUBLE;
		size = 2;
		break;
	case EDK3::T_DOUBLE_3:
		data_type = GL_DOUBLE;
		size = 3;
		break;
	case EDK3::T_DOUBLE_4:
		data_type = GL_DOUBLE;
		size = 4;
		break;



	}

	glVertexAttribPointer(attribute_index, size, data_type, normalized, stride, (void*)(offset));
	buffer->bind(EDK3::dev::Buffer::kTarget_Vertex_Data);

	glEnableVertexAttribArray(attribute_index);


}

void HORCHATA::GPUManager::disableVertexAttribute(const unsigned int attrib_index)
{
	glDisableVertexAttribArray(attrib_index);
}

void HORCHATA::GPUManager::drawElements(const DrawMode mode, unsigned int count, const EDK3::dev::Buffer * buffer, const EDK3::Type element_type, const unsigned int offset) const
{

	GLenum data_mode;
	GLenum data_type;

	switch (mode) {

	case EDK3::dev::GPUManager::kDrawMode_LineLoop:
		data_mode = GL_LINE_LOOP;
		break;

	case EDK3::dev::GPUManager::kDrawMode_Lines:
		data_mode = GL_LINES;
		break;

	case EDK3::dev::GPUManager::kDrawMode_LineStrip:
		data_mode = GL_LINE_STRIP;
		break;

	case EDK3::dev::GPUManager::kDrawMode_Points:
		data_mode = GL_POINTS;
		break;

	case EDK3::dev::GPUManager::kDrawMode_Triangles:
		data_mode = GL_TRIANGLES;
		break;

	case EDK3::dev::GPUManager::kDrawMode_TriangleStrip:
		data_mode = GL_TRIANGLE_STRIP;
		break;

	}

	switch (element_type) {

	case EDK3::T_BYTE:
		data_type = GL_BYTE;
		break;

	case EDK3::T_UBYTE:
		data_type = GL_UNSIGNED_BYTE;
		break;
	
	case EDK3::T_SHORT:
		data_type = GL_SHORT;
		break;
	
	case EDK3::T_USHORT:
		data_type = GL_UNSIGNED_SHORT;
		break;

	case EDK3::T_INT:
		data_type = GL_INT;
		break;

	case EDK3::T_UINT:
		data_type = GL_UNSIGNED_INT;
		break;
	}

	buffer->bind(EDK3::dev::Buffer::kTarget_Elements);

	glDrawElements(data_mode, count, data_type, (void*)offset);

}

void HORCHATA::GPUManager::enableDepthTest(const CompareFunc f)
{

	GLenum func_type;

	switch (f) {
		
	case kCompareFunc_Always:
		func_type = GL_ALWAYS;
		break;

	case kCompareFunc_Equal:
		func_type = GL_EQUAL;
		break;

	case kCompareFunc_Greater:
		func_type = GL_GREATER;
		break;

	case kCompareFunc_GreaterOrEqual:
		func_type = GL_GEQUAL;
		break;

	case kCompareFunc_Less:
		func_type = GL_LESS;
		break;

	case kCompareFunc_LessOrEqual:
		func_type = GL_LEQUAL;
		break;

	case kCompareFunc_Never:
		func_type = GL_NEVER;
		break;

	case kCompareFunc_NotEqual:
		func_type = GL_NOTEQUAL;
		break;

	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(func_type);

}

void HORCHATA::GPUManager::disableDepthTest()
{

	glDisable(GL_DEPTH_TEST);

}

void HORCHATA::GPUManager::enableBlend(BlendParam source, 
	BlendParam destination, 
	BlendOp operation, 
	const float ConstantColor[4])
{

	GLenum data_source;
	GLenum data_destination;
	GLenum data_operation;

	float color[4];

	switch (source) {

	case EDK3::dev::GPUManager::kBlendParam_ConstantAlpha:
		data_source = GL_CONSTANT_ALPHA;
		data_destination = GL_CONSTANT_ALPHA;
		break;

	case EDK3::dev::GPUManager::kBlendParam_ConstantColor:
		data_source = GL_CONSTANT_COLOR;
		data_destination = GL_CONSTANT_COLOR;
		break;

	case EDK3::dev::GPUManager::kBlendParam_DestinationAlpha:
		data_source = GL_DST_ALPHA;
		data_destination = GL_DST_ALPHA;
		break;

	case EDK3::dev::GPUManager::kBlendParam_DestinationColor:
		data_source = GL_DST_COLOR;
		data_destination = GL_DST_COLOR;
		break;

	case EDK3::dev::GPUManager::kBlendParam_One:
		data_source = GL_ONE;
		data_destination = GL_ONE;
		break;

	case EDK3::dev::GPUManager::kBlendParam_OneMinusConstantAlpha:
		data_source = GL_ONE_MINUS_CONSTANT_ALPHA;
		data_destination = GL_ONE_MINUS_CONSTANT_ALPHA;
		break;

	case EDK3::dev::GPUManager::kBlendParam_OneMinusConstantColor:
		data_source = GL_ONE_MINUS_CONSTANT_COLOR;
		data_destination = GL_ONE_MINUS_CONSTANT_COLOR;
		break;

	case EDK3::dev::GPUManager::kBlendParam_OneMinusDestinationAlpha:
		data_source = GL_ONE_MINUS_DST_ALPHA;
		data_destination = GL_ONE_MINUS_DST_ALPHA;
		break;

	case EDK3::dev::GPUManager::kBlendParam_OneMinusDestinationColor:
		data_source = GL_ONE_MINUS_DST_COLOR;
		data_destination = GL_ONE_MINUS_DST_COLOR;
		break;

	case EDK3::dev::GPUManager::kBlendParam_OneMinusSourceAlpha:
		data_source = GL_ONE_MINUS_SRC_ALPHA;
		data_destination = GL_ONE_MINUS_SRC_ALPHA;
		break;

	case EDK3::dev::GPUManager::kBlendParam_OneMinusSourceColor:
		data_source = GL_ONE_MINUS_SRC_COLOR;
		data_destination = GL_ONE_MINUS_SRC_COLOR;
		break;

	case EDK3::dev::GPUManager::kBlendParam_SourceAlpha:
		data_source = GL_SRC_ALPHA;
		data_destination = GL_SRC_ALPHA;
		break;

	case EDK3::dev::GPUManager::kBlendParam_SourceAlphaSaturate:
		data_source = GL_SRC_ALPHA_SATURATE;
		data_destination = GL_SRC_ALPHA_SATURATE;
		break;

	case EDK3::dev::GPUManager::kBlendParam_SourceColor:
		data_source = GL_SRC_COLOR;
		data_destination = GL_SRC_COLOR;
		break;

	case EDK3::dev::GPUManager::kBlendParam_Zero:
		data_source = GL_ZERO;
		data_destination = GL_ZERO;
		break;

	}

	switch (operation) {

	case EDK3::dev::GPUManager::kBlendOp_Add:
		data_operation = GL_FUNC_ADD;
		break;

	case EDK3::dev::GPUManager::kBlendOp_Max:
		data_operation = GL_MAX;
		break;

	case EDK3::dev::GPUManager::kBlendOp_Min:
		data_operation = GL_MIN;
		break;

	case EDK3::dev::GPUManager::kBlendOp_ReverseSubtract:
		data_operation = GL_FUNC_REVERSE_SUBTRACT;
		break;

	case EDK3::dev::GPUManager::kBlendOp_Subtract:
		data_operation = GL_FUNC_SUBTRACT;
		break;

	}

	if (ConstantColor) {

		for (int i = 0; i < 4; i++) {

			color[i] = ConstantColor[i];

		}

	}

	glBlendFunc(data_source, data_destination);

	glBlendEquation(data_operation);
	glBlendColor(color[0], color[1], color[2], color[3]);

	glEnable(GL_BLEND);

}

void HORCHATA::GPUManager::enableCullFaces(const FaceType f)
{

	glEnable(GL_CULL_FACE);

	switch (f) {

	case kFace_Back:
		glCullFace(GL_BACK);
		break;

	case kFace_Front:
		glCullFace(GL_FRONT);
		break;

	case kFace_FrontAndBack:
		glCullFace(GL_FRONT_AND_BACK);
		break;
	}

}

void HORCHATA::GPUManager::disableCullFaces()
{

	glDisable(GL_CULL_FACE);

}

void HORCHATA::GPUManager::enableScissor(int x, 
	int y, 
	unsigned int width, 
	unsigned int height)
{

	glEnable(GL_SCISSOR_TEST);
	glScissor(x, y, width, height);

}

void HORCHATA::GPUManager::disableScissor()
{

	glDisable(GL_SCISSOR_TEST);

}

void HORCHATA::GPUManager::changeColorMask(const bool red, 
	const bool green, 
	const bool blue, 
	const bool alpha)
{

	glColorMask(red, green, blue, alpha);

}

void HORCHATA::GPUManager::changeDepthMask(bool enable)
{

	glDepthMask(enable);

}
