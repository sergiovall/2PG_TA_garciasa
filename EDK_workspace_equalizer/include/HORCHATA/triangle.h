#include <EDK3/geometry.h>

class Triangle : public EDK3::Geometry{

public:

	virtual bool bindAttribute(const EDK3::Attribute a, unsigned int where_to_bind_attribute) const override;

	virtual void render() const override;

	void generate();

private:
	EDK3::ref_ptr<EDK3::dev::Buffer> vertex_buffer;
	EDK3::ref_ptr<EDK3::dev::Buffer> index_buffer;
	

};