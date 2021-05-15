#include <HORCHATA/horchata_texture.h>

HORCHATA::Texture::Texture() {

}

HORCHATA::Texture::~Texture() {

}

void HORCHATA::Texture::set_data(const Format f, 
	const EDK3::Type t, 
	const void * data, 
	unsigned int mipmap_LOD)
{

	GLenum data_format;
	GLenum data_type;
	GLenum id;

	switch (f) {

	case EDK3::Texture::F_BGR:
		data_format = GL_BGR;
		break;

	case EDK3::Texture::F_BGRA:
		data_format = GL_BGRA;
		break;

	case EDK3::Texture::F_DEPTH:
		data_format = GL_DEPTH;
		break;

	case EDK3::Texture::F_DEPTH32:
		data_format = GL_DEPTH;
		break;

	case EDK3::Texture::F_R:
		data_format = GL_R;
		break;

	case EDK3::Texture::F_RG:
		data_format = GL_RG;
		break;

	case EDK3::Texture::F_RGB:
		data_format = GL_RGB;
		break;

	case EDK3::Texture::F_RGBA:
		data_format = GL_RGBA;
		break;

	}

	switch (t) {

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

	switch (format_) {

	case EDK3::Texture::F_BGR:
		id = GL_BGR;
		break;

	case EDK3::Texture::F_BGRA:
		id = GL_BGRA;
		break;

	case EDK3::Texture::F_DEPTH:
		id = GL_DEPTH;
		break;

	case EDK3::Texture::F_DEPTH32:
		id = GL_DEPTH;
		break;

	case EDK3::Texture::F_R:
		id = GL_R;
		break;

	case EDK3::Texture::F_RG:
		id = GL_RG;
		break;

	case EDK3::Texture::F_RGB:
		id = GL_RGB;
		break;

	case EDK3::Texture::F_RGBA:
		id = GL_RGBA;
		break;

	}

	switch (type_) {

	case EDK3::Texture::T_1D:
		glTexImage1D(GL_TEXTURE_1D, mipmap_LOD, id, width_,0, data_format, data_type, data);
		break;

	case EDK3::Texture::T_2D:
		glTexImage2D(GL_TEXTURE_2D, mipmap_LOD, id, width_, height_, 0, data_format, data_type, data);
		break;

	case EDK3::Texture::T_3D:
		glTexImage3D(GL_TEXTURE_3D, mipmap_LOD, id, width_, height_, depth_, 0, data_format, data_type, data);
		break;

	}

}

void HORCHATA::Texture::bind(unsigned int textUnit) const
{

	GLenum tex_target;

	glActiveTexture(GL_TEXTURE0 + textUnit);

	switch (type_) {

	case EDK3::Texture::T_1D:
		tex_target = GL_TEXTURE_1D;
		break;

	case EDK3::Texture::T_2D:
		tex_target = GL_TEXTURE_2D;
		break;

	case EDK3::Texture::T_3D:
		tex_target = GL_TEXTURE_3D;
		break;

	case EDK3::Texture::T_CUBEMAP:
		tex_target = GL_TEXTURE_CUBE_MAP;
		break;

	}

	glBindTexture(tex_target, texture_id);

}

unsigned int HORCHATA::Texture::internal_id() const{return texture_id;}

void HORCHATA::Texture::set_min_filter(Filter f) {

	set_min_filter(f);// Creo que lo tengo que hacer con EDK3::Texture::

	GLuint filter_type;

	switch (f) {

	case EDK3::Texture::F_NEAREST:
		filter_type = GL_NEAREST;
		break;

	case EDK3::Texture::F_LINEAR:
		filter_type = GL_LINEAR;
		break;

	case EDK3::Texture::F_NEAREST_MIPMAP_LINEAR:
		filter_type = GL_NEAREST_MIPMAP_LINEAR;
		break;

	case EDK3::Texture::F_LINEAR_MIPMAP_NEAREST:
		filter_type = GL_LINEAR_MIPMAP_NEAREST;
		break;

	case EDK3::Texture::F_LINEAR_MIPMAP_LINEAR:
		filter_type = GL_LINEAR_MIPMAP_LINEAR;
		break;

	case EDK3::Texture::F_NEAREST_MIPMAP_NEAREST:
		filter_type = F_NEAREST_MIPMAP_NEAREST;
		break;
		
	}

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_type);

}

void HORCHATA::Texture::set_mag_filter(Filter f) {

	set_mag_filter(f);

	GLuint filter_type;

	switch (f) {

	case EDK3::Texture::F_NEAREST:
		filter_type = GL_NEAREST;
		break;

	case EDK3::Texture::F_LINEAR:
		filter_type = GL_LINEAR;
		break;

	case EDK3::Texture::F_NEAREST_MIPMAP_LINEAR:
		filter_type = GL_NEAREST_MIPMAP_LINEAR;
		break;

	case EDK3::Texture::F_LINEAR_MIPMAP_NEAREST:
		filter_type = GL_LINEAR_MIPMAP_NEAREST;
		break;

	case EDK3::Texture::F_LINEAR_MIPMAP_LINEAR:
		filter_type = GL_LINEAR_MIPMAP_LINEAR;
		break;

	case EDK3::Texture::F_NEAREST_MIPMAP_NEAREST:
		filter_type = F_NEAREST_MIPMAP_NEAREST;
		break;

	}

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_type);

}

void HORCHATA::Texture::set_wrap_s(Wrap c) {

	set_wrap_s(c);

	GLuint wrap_type;

	switch (c) {

	case EDK3::Texture::W_CLAMP_TO_EDGE:
		wrap_type = GL_CLAMP_TO_EDGE;
		break;

	case EDK3::Texture::W_MIRRORED_REPEAT:
		wrap_type = GL_MIRRORED_REPEAT;
		break;

	case EDK3::Texture::W_REPEAT:
		wrap_type = GL_REPEAT;
		break;

	}

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_type);

}

void HORCHATA::Texture::set_wrap_t(Wrap c) {

	set_wrap_t(c);

	GLuint wrap_type;

	switch (c) {

	case EDK3::Texture::W_CLAMP_TO_EDGE:
		wrap_type = GL_CLAMP_TO_EDGE;
		break;

	case EDK3::Texture::W_MIRRORED_REPEAT:
		wrap_type = GL_MIRRORED_REPEAT;
		break;

	case EDK3::Texture::W_REPEAT:
		wrap_type = GL_REPEAT;
		break;

	}

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_type);

}

void HORCHATA::Texture::set_wrap_r(Wrap c) {

	set_wrap_r(c);

	GLuint wrap_type;

	switch (c) {

	case EDK3::Texture::W_CLAMP_TO_EDGE:
		wrap_type = GL_CLAMP_TO_EDGE;
		break;

	case EDK3::Texture::W_MIRRORED_REPEAT:
		wrap_type = GL_MIRRORED_REPEAT;
		break;

	case EDK3::Texture::W_REPEAT:
		wrap_type = GL_REPEAT;
		break;

	}

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, wrap_type);

}

void HORCHATA::Texture::generateMipmaps() const{

	GLenum target;

	switch (type_) {

	case EDK3::Texture::T_1D:
		target = GL_TEXTURE_1D;
		break;

	case EDK3::Texture::T_2D:
		target = GL_TEXTURE_2D;
		break;

	case EDK3::Texture::T_3D:
		target = GL_TEXTURE_3D;
		break;

	case EDK3::Texture::T_CUBEMAP:
		target = GL_TEXTURE_CUBE_MAP;
		break;
	}

	glGenerateMipmap(target);


}