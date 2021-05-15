#ifndef __INCLUDE_HORCHATA_TEXTURE__
#define __INCLUDE_HORCHATA_TEXTURE__ 1

#include <EDK3/texture.h>
#include <EDK3/dev/opengl.h>


namespace HORCHATA {

	class Texture : public EDK3::Texture {
	public:

		Texture();
		~Texture();


		virtual void set_data(
			const Format f, 
			const EDK3::Type t,   
			const void *data,  
			unsigned int mipmap_LOD = 0) override; 

		virtual void bind(unsigned int textUnit) const override;
		virtual unsigned int internal_id() const override;

		virtual void set_min_filter(Filter f) override;
		virtual void set_mag_filter(Filter f)override;
		virtual void set_wrap_s(Wrap c)override;
		virtual void set_wrap_t(Wrap c)override;
		virtual void set_wrap_r(Wrap c)override;
		virtual void generateMipmaps() const override;


	private:
		Type type_;
		Format format_;
		unsigned int width_;
		unsigned int height_;
		unsigned int depth_;
		Filter min_filter_;
		Filter mag_filter_;
		Wrap  wrap_s_;
		Wrap  wrap_t_;
		Wrap  wrap_r_;

		Texture(const Texture&);
		Texture& operator=(const Texture&);

		GLint texture_id;
	};

}

#endif