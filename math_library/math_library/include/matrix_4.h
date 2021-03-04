#ifndef __MATRIX4_H__
#define __MATRIX4_H__ 1

#include "vector_3.h"
#include "vector_4.h"
#include "matrix_3.h"

class Matix4x4{
 public:

  Matix4x4();
  Matix4x4(float a[16]);
  Matix4x4(float value);
  Matix4x4(const Matix4x4& copy);
  ~Matix4x4();

  Matix4x4 Identity() const;
  Matix4x4 Multiply(const Matix4x4& other) const;

  float Determinant() const;
  Matix4x4 Adjoint() const;
  bool GetInverse(Matix4x4* out) const;
  bool Inverse();

  Matix4x4 Transpose() const;


  static Matix4x4 Translate(const Vector3& distance);
  static Matix4x4 Translate(float x, float y, float z);

  static Matix4x4 Scale(const Vector3& scale);
  static Matix4x4 Scale(float x, float y, float z);

  static Matix4x4 RotateX(float radians);
  static Matix4x4 RotateY(float radians);
  static Matix4x4 RotateZ(float radians);

  static Matix4x4 GetTransform(const Vector3& translate, const Vector3& scale,
                      float rotateX, float rotateY, float rotateZ);

  static Matix4x4 GetTransform(float trans_x, float trans_y, float trans_z,
                      float scale_x, float scale_y, float scale_Z,
                      float rotateX, float rotateY, float rotateZ);

  Matix4x4 PerspectiveMatrix(float fov, float aspect,
	  float near, float far) const;

  Matix4x4 OrthoMatrix(float right, float left, float top, float valueottom,
	  float near, float far) const;

  Vector4 GetColum(int colum) const;
  Vector4 GetLine(int line) const;

  Matix4x4 operator+(const Matix4x4& other) const;
  Matix4x4& operator+=(const Matix4x4& other);
  Matix4x4 operator+(float value) const;
  Matix4x4& operator+=(float value);
  Matix4x4 operator-(const Matix4x4& other) const;
  Matix4x4& operator-=(const Matix4x4& other);
  Matix4x4 operator-(float value) const;
  Matix4x4& operator-=(float value);
  Matix4x4& operator*=(float value);
  Matix4x4 operator*(float value) const;
  Matix4x4& operator/=(float value);
  Matix4x4 operator/(float value) const;
  bool operator==(const Matix4x4& other);
  bool operator!=(const Matix4x4& other);
  void operator=(const Matix4x4& other);

  float m[16];
};


inline Matix4x4::Matix4x4() {

}

inline Matix4x4::Matix4x4(float values[16]) {
	for (int i = 0; i < 16; i++) {
		m[i] = values[i];
	}

}

inline Matix4x4::Matix4x4(float value) {

	for (int i = 0; i < 16; i++) {
		m[i] = value;
	}
	
}

inline Matix4x4::Matix4x4(const Matix4x4& copy) {
	for (int i = 0; i < 16; i++) {
		m[i] = copy.m[i];
	}
}

inline Matix4x4::~Matix4x4() {

}

inline Matix4x4 Matix4x4::Identity() const {
	float values[16]{ 1.0f,0.0f,0.0f,0.0f,
					0.0f, 1.0f ,0.0f ,0.0f ,
					0.0f ,0.0f ,1.0f ,0.0f,
					0.0f ,0.0f ,0.0f ,1.0f };
	return Matix4x4(values);
}

inline Matix4x4 Matix4x4::Multiply(const Matix4x4& other)const  {
	Matix4x4 result;
	Vector4 a, b;

	for (int i = 0; i < 16; i++) {

		if (i % 4 == 0) {
			b = { other.m[0],other.m[4],other.m[8], other.m[12] };
		}
		else {
			if (i % 4 == 1) {
				b = { other.m[1],other.m[5],other.m[9],other.m[13] };
			}
			else {
				if (i % 4 == 2) {

					b = { other.m[2],other.m[6],other.m[10], other.m[14] };

				}
				else {

					b = { other.m[3],other.m[7],other.m[11], other.m[15] };

				}
			}
		}
		if (i / 4 == 0) {
			a = { m[0],m[1],m[2],m[3] };
		}
		else {
			if (i / 4 == 1) {
				a = { m[4],m[5],m[6],m[7] };
			}
			else {
				if (i / 4 == 2) {
					a = { m[8],m[9],m[10],m[11] };
				}
				else {

					a = { m[12],m[13],m[14],m[15] };

				}
			}
		}

		result.m[i] = a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;

	}

	return result;

}


inline float Matix4x4::Determinant() const {
	
	return m[0] * (((m[5] * m[10] * m[15]) + (m[6] * m[11] * m[13]) + (m[14] * m[9] * m[7])) -
		((m[13] * m[10] * m[7]) + (m[14] * m[11] * m[5]) + (m[6] * m[9] * m[15]))) + m[1] * (((m[4] * m[10] * m[15]) + (m[6] * m[11] * m[12]) + (m[14] * m[8] * m[7])) -
		((m[12] * m[10] * m[7]) + (m[14] * m[11] * m[4]) + (m[6] * m[8] * m[15])))* -1.0f + m[2] * (((m[4] * m[9] * m[15]) + (m[5] * m[11] * m[12]) + (m[13] * m[8] * m[7])) -
		((m[12] * m[9] * m[7]) + (m[13] * m[11] * m[4]) + (m[5] * m[8] * m[15]))) + m[3] * (((m[4] * m[9] * m[14]) + (m[5] * m[10] * m[12]) + (m[13] * m[8] * m[6])) -
		((m[12] * m[9] * m[6]) + (m[13] * m[10] * m[4]) + (m[5] * m[8] * m[14]))) * -1.0f;

}


inline Matix4x4 Matix4x4::Adjoint() const {
	
	Matix4x4 result;
	Matrix3x3 det;
	det.m[0] = m[5];
	det.m[1] = m[6];
	det.m[2] = m[7];
	det.m[3] = m[9];
	det.m[4] = m[10];
	det.m[5] = m[11];
	det.m[6] = m[13];
	det.m[7] = m[14];
	det.m[8] = m[15];

	result.m[0] = det.Determinant();
	det = det.Identity();

	det.m[0] = m[4];
	det.m[1] = m[6];
	det.m[2] = m[7];
	det.m[3] = m[8];
	det.m[4] = m[10];
	det.m[5] = m[11];
	det.m[6] = m[12];
	det.m[7] = m[14];
	det.m[8] = m[15];

	result.m[1] = det.Determinant() * -1.0f;
	det = det.Identity();

	det.m[0] = m[4];
	det.m[1] = m[5];
	det.m[2] = m[7];
	det.m[3] = m[8];
	det.m[4] = m[9];
	det.m[5] = m[11];
	det.m[6] = m[12];
	det.m[7] = m[13];
	det.m[8] = m[15];

	result.m[2] = det.Determinant();
	det = det.Identity();

	det.m[0] = m[4];
	det.m[1] = m[5];
	det.m[2] = m[6];
	det.m[3] = m[8];
	det.m[4] = m[9];
	det.m[5] = m[10];
	det.m[6] = m[12];
	det.m[7] = m[13];
	det.m[8] = m[14];

	result.m[3] = det.Determinant() * -1.0f;
	det = det.Identity();

	det.m[0] = m[1];
	det.m[1] = m[2];
	det.m[2] = m[3];
	det.m[3] = m[9];
	det.m[4] = m[10];
	det.m[5] = m[11];
	det.m[6] = m[13];
	det.m[7] = m[14];
	det.m[8] = m[15];

	result.m[4] = det.Determinant() * -1.0f;
	det = det.Identity();

	det.m[0] = m[0];
	det.m[1] = m[2];
	det.m[2] = m[3];
	det.m[3] = m[8];
	det.m[4] = m[10];
	det.m[5] = m[11];
	det.m[6] = m[12];
	det.m[7] = m[14];
	det.m[8] = m[15];

	result.m[5] = det.Determinant();
	det = det.Identity();

	det.m[0] = m[0];
	det.m[1] = m[1];
	det.m[2] = m[3];
	det.m[3] = m[8];
	det.m[4] = m[9];
	det.m[5] = m[11];
	det.m[6] = m[12];
	det.m[7] = m[13];
	det.m[8] = m[15];

	result.m[6] = det.Determinant() * -1.0f;
	det = det.Identity();

	det.m[0] = m[0];
	det.m[1] = m[1];
	det.m[2] = m[2];
	det.m[3] = m[8];
	det.m[4] = m[9];
	det.m[5] = m[10];
	det.m[6] = m[12];
	det.m[7] = m[13];
	det.m[8] = m[14];

	result.m[7] = det.Determinant();
	det = det.Identity();

	det.m[0] = m[1];
	det.m[1] = m[2];
	det.m[2] = m[3];
	det.m[3] = m[5];
	det.m[4] = m[6];
	det.m[5] = m[7];
	det.m[6] = m[13];
	det.m[7] = m[14];
	det.m[8] = m[15];

	result.m[8] = det.Determinant();
	det = det.Identity();

	det.m[0] = m[0];
	det.m[1] = m[2];
	det.m[2] = m[3];
	det.m[3] = m[4];
	det.m[4] = m[6];
	det.m[5] = m[7];
	det.m[6] = m[12];
	det.m[7] = m[14];
	det.m[8] = m[15];

	result.m[9] = det.Determinant() * -1.0f;
	det = det.Identity();

	det.m[0] = m[0];
	det.m[1] = m[1];
	det.m[2] = m[3];
	det.m[3] = m[4];
	det.m[4] = m[5];
	det.m[5] = m[7];
	det.m[6] = m[12];
	det.m[7] = m[13];
	det.m[8] = m[15];

	result.m[10] = det.Determinant();
	det = det.Identity();

	det.m[0] = m[0];
	det.m[1] = m[1];
	det.m[2] = m[2];
	det.m[3] = m[4];
	det.m[4] = m[5];
	det.m[5] = m[6];
	det.m[6] = m[12];
	det.m[7] = m[13];
	det.m[8] = m[14];

	result.m[11] = det.Determinant() * -1.0f;
	det = det.Identity();

	det.m[0] = m[1];
	det.m[1] = m[2];
	det.m[2] = m[3];
	det.m[3] = m[5];
	det.m[4] = m[6];
	det.m[5] = m[7];
	det.m[6] = m[9];
	det.m[7] = m[10];
	det.m[8] = m[11];

	result.m[12] = det.Determinant() * -1.0f;
	det = det.Identity();

	det.m[0] = m[0];
	det.m[1] = m[2];
	det.m[2] = m[3];
	det.m[3] = m[4];
	det.m[4] = m[6];
	det.m[5] = m[7];
	det.m[6] = m[8];
	det.m[7] = m[10];
	det.m[8] = m[11];

	result.m[13] = det.Determinant();
	det = det.Identity();

	det.m[0] = m[0];
	det.m[1] = m[1];
	det.m[2] = m[3];
	det.m[3] = m[4];
	det.m[4] = m[5];
	det.m[5] = m[7];
	det.m[6] = m[8];
	det.m[7] = m[9];
	det.m[8] = m[11];

	result.m[14] = det.Determinant() * -1.0f;
	det = det.Identity();

	det.m[0] = m[0];
	det.m[1] = m[1];
	det.m[2] = m[2];
	det.m[3] = m[4];
	det.m[4] = m[5];
	det.m[5] = m[6];
	det.m[6] = m[8];
	det.m[7] = m[9];
	det.m[8] = m[10];

	result.m[15] = det.Determinant();
	det = det.Identity();
	return result;
}

inline bool Matix4x4::Inverse() {
	float det = Determinant();
	if (det != 0.0f) {
		*this = (Adjoint().Transpose() / det);
		return true;
	}
	return false;
}

inline bool Matix4x4::GetInverse(Matix4x4* out) const {
	return out->Inverse();

}

inline Matix4x4 Matix4x4::Transpose() const {
		
	float new_values[16] = { m[0], m[4], m[8], m[12],
						m[1], m[5], m[9], m[13],
						m[2], m[6], m[10],m[14],
						m[3], m[7], m[11],m[15] };
	return Matix4x4(new_values);
}

inline Matix4x4 Matix4x4::Translate(const Vector3& distance){
	
	float new_values[16] = { 1.0f, 0.0f, 0.0f, distance.x,
							0.0f, 1.0f, 0.0f, distance.y,
							0.0f, 0.0f, 1.0f, distance.z,
							0.0f, 0.0f, 0.0f, 1.0f };

	return Matix4x4(new_values);
}

inline Matix4x4 Matix4x4::Translate(float x, float y, float z){
	
	Matix4x4 result;
	result = result.Identity();
	result.m[3] = x;
	result.m[7] = y;
	result.m[11] = z;
	return result;
}

inline Matix4x4 Matix4x4::Scale(const Vector3& scale){
	
	Matix4x4 result;
	result = result.Identity();
	result.m[0] = scale.x;
	result.m[5] = scale.y;
	result.m[10] = scale.z;
	return result;
}

inline Matix4x4 Matix4x4::Scale(float x, float y, float z){
	
	Matix4x4 result;
	result = result.Identity();
	result.m[0] = x;
	result.m[5] = y;
	result.m[10] = z;
	return result;
}

inline Matix4x4 Matix4x4::RotateX(float radians){
	
	Matix4x4 result;
	result = result.Identity();
	result.m[5] = cosf(radians);
	result.m[6] = -sinf(radians);
	result.m[9] = sinf(radians);
	result.m[10] = cosf(radians);
	return result;
}

inline Matix4x4 Matix4x4::RotateY(float radians){
	
	Matix4x4 result;
	result = result.Identity();
	result.m[0] = cosf(radians);
	result.m[2] = sinf(radians);
	result.m[8] = -sinf(radians);
	result.m[10] = cosf(radians);
	return result;
}

inline Matix4x4 Matix4x4::RotateZ(float radians) {
	
	Matix4x4 result;
	result = result.Identity();
	result.m[0] = cosf(radians);
	result.m[1] = -sinf(radians);
	result.m[4] = sinf(radians);
	result.m[5] = cosf(radians);
	return result;
}

inline Matix4x4 Matix4x4::GetTransform(const Vector3& translate,
								const Vector3& scale,
								float rotateX, float rotateY,
								float rotateZ)   {
	Matix4x4 result;
	result = result.Identity();
	result = result.Multiply(result.Scale(scale));
	result = result.Multiply(result.RotateX(rotateX));
	result = result.Multiply(result.RotateY(rotateY));
	result = result.Multiply(result.RotateZ(rotateZ));
	result = result.Multiply(result.Translate(translate));
	return result;
}

inline Matix4x4 Matix4x4::GetTransform(float trans_x, float trans_y, float trans_z,
	float scale_x, float scale_y, float scale_z,
	float rotateX, float rotateY, float rotateZ)  {
	
	Matix4x4 result;

	result = result.Identity();
	result = result.Multiply(result.Scale(scale_x, scale_y, scale_z));
	result = result.Multiply(result.RotateX(rotateX));
	result = result.Multiply(result.RotateY(rotateY));
	result = result.Multiply(result.RotateZ(rotateZ));
	result = result.Multiply(result.Translate(trans_x, trans_y, trans_z));

	return result;
}

inline Vector4 Matix4x4::GetColum(int colum) const {
	return Vector4(m[colum], m[colum + 3], m[colum + 6],m[colum + 9]);
}

inline Vector4 Matix4x4::GetLine(int line) const {
	return Vector4(m[(line) * 4], m[(line) * 4 + 1], m[((line) * 4 + 2)], m[((line) * 4 + 3)]);
}

inline Matix4x4 Matix4x4::PerspectiveMatrix(float fov, float aspect,
	float near, float far) const {
	
	Matix4x4 result = Identity();
	float fov_rad = (fov / 180.0f) * 3.141592f;
	float aux = 1.0f / tanf(fov_rad * 0.5f);
	result.m[0] = fov_rad / aspect;
	result.m[5] = fov_rad;
	result.m[10] = (fov_rad + near) / (near - fov_rad);
	result.m[14] = -1.0f;
	result.m[11] = (2.0f * fov_rad * near) / (near - fov_rad);
	return result;
}

inline Matix4x4 Matix4x4::OrthoMatrix(float right, float left, float top, float bottom,
	float near, float far) const {

	float m_x = (left + right) / 2.0f;
	float m_y = (bottom + top) / 2.0f;
	float m_z = ((-near) + (-far)) / 2.0f;
	float scale_x = 2.0f / (right - left);
	float scale_y = 2.0f / (top - bottom);
	float scale_z = 2.0f / (far - near);
	Matix4x4 result;
	result.m[0] = scale_x;
	result.m[5] = scale_y;
	result.m[10] = scale_z;
	result.m[3] = m_x;
	result.m[7] = m_y;
	result.m[11] = m_z;
	return result;
}



inline Matix4x4 Matix4x4::operator+(const Matix4x4& other) const {
	float aux[16];
	for (int i = 0; i < 9; i++) {
		*(aux + i) = m[i] + other.m[i];
	}
	return Matix4x4(aux);
}

inline Matix4x4& Matix4x4::operator+=(const Matix4x4& other) {
	for (int i = 0; i < 16; i++) {
		m[i] += other.m[i];
	}
	return *this;
}

inline Matix4x4 Matix4x4::operator+(float value) const {
	float aux[16];
	for (int i = 0; i < 16; i++) {
		*(aux + i) = m[i] + value;
	}
	return Matix4x4(aux);
}

inline Matix4x4& Matix4x4::operator+=(float value) {	
	for (int i = 0; i < 16; i++) {
		m[i] += value;
	}
	return *this;
}


inline Matix4x4 Matix4x4::operator-(const Matix4x4& other) const  {
	float aux[16];
	for (int i = 0; i < 16; i++) {
		*(aux + i) = m[i] - other.m[i];
	}
	return Matix4x4(aux);
}

inline Matix4x4& Matix4x4::operator-=(const Matix4x4& other) {
	for (int i = 0; i < 16; i++) {
		m[i] -= other.m[i];
	}
	return *this;
}

inline Matix4x4 Matix4x4::operator-(float value) const  {
	float aux[16];
	for (int i = 0; i < 16; i++) {
		*(aux + i) = m[i] - value;
	}
	return Matix4x4(aux);
}

inline Matix4x4& Matix4x4::operator-=(float value) {
	for (int i = 0; i < 16; i++) {
		m[i] -= value;
	}
	return *this;
}

inline Matix4x4& Matix4x4::operator*=(float value) {
	for (int i = 0; i < 16; i++) {
		m[i] *= value;
	}
	return *this;
}

inline Matix4x4 Matix4x4::operator*(float value) const  {
	float aux[16];
	for (int i = 0; i < 16; i++) {
		*(aux + i) = m[i] * value;
	}
	return Matix4x4(aux);
}

inline Matix4x4& Matix4x4::operator/=(float value) {
	for (int i = 0; i < 16; i++) {
		m[i] /= value;
	}
	return *this;
}

inline Matix4x4 Matix4x4::operator/(float value) const {
	float aux[16];
	for (int i = 0; i < 16; i++) {
		aux[i] = m[i] / value;
	}
	return Matix4x4(aux);
}

inline bool Matix4x4::operator==(const Matix4x4& other) {

	bool equal = true;

	for (int i = 0; i < 16 && equal; i++) {
		equal &= (m[i] == other.m[i]);
	}

	return equal;
}

inline bool Matix4x4::operator!=(const Matix4x4& other) {
	
	bool notequal = true;

	for (int i = 0; i < 16 && notequal; i++) {
		notequal &= (m[i] != other.m[i]);
	}

	return notequal;
}

inline void Matix4x4::operator=(const Matix4x4& other) {
	for (int i = 0; i < 16; i++) {
		m[i] = other.m[i];
	}
}

#endif
