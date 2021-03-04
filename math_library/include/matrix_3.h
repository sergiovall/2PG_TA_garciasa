#ifndef __MATRIX3_H__
#define __MATRIX3_H__ 1

#include "vector_2.h"
#include "vector_3.h"

class Matrix3x3 {
public:

	Matrix3x3();
	Matrix3x3(float *values_array);
	Matrix3x3(float value);
	Matrix3x3(Vector3 a, Vector3 b, Vector3 c);

	Matrix3x3(const Matrix3x3& copy);
	~Matrix3x3();

	static Matrix3x3 Identity();

	Matrix3x3 Multiply(const Matrix3x3& other) const;

	float Determinant() const;

	Matrix3x3 Adjoint() const;
	bool GetInverse(Matrix3x3& out) const;
	bool Inverse();

	Matrix3x3 Transpose() const;

	static Matrix3x3 Translate(const Vector2& position);
	static Matrix3x3 Translate(float x, float y);

	Vector3 GetColum(int colum) const;
	Vector3 GetLine(int line) const;

	inline Matrix3x3 operator+(const Matrix3x3& other) const;
	inline Matrix3x3& operator+=(const Matrix3x3& other);
	inline Matrix3x3 operator+(float value) const;
	inline Matrix3x3& operator+=(float value);
	inline Matrix3x3 operator-(const Matrix3x3& other) const;
	inline Matrix3x3& operator-=(const Matrix3x3& other);
	inline Matrix3x3 operator-(float value) const;
	inline Matrix3x3& operator-=(float value);
	inline Matrix3x3 operator*(float value) const;
	inline Matrix3x3& operator*=(float value);
	inline Matrix3x3 operator/(float value) const;
	inline Matrix3x3& operator/=(float value);
	bool operator==(const Matrix3x3& other) const;
	bool operator!=(const Matrix3x3& other) const;
	inline void operator=(const Matrix3x3& other);

	float m[9];
};


inline Matrix3x3::Matrix3x3() {
}

inline Matrix3x3::Matrix3x3(float value) {
	for (int i = 0; i < 9; i++) {
		m[i] = value;
	}
}

inline Matrix3x3::Matrix3x3(float *values_array) {
	for (int i = 0; i < 9; i++) {
		m[i] = values_array[i];
	}

}

inline Matrix3x3::Matrix3x3(Vector3 a, Vector3 b, Vector3 c) {
	float aux[9] = { a.x,a.y,a.z,b.x,b.y,b.z,c.x,c.y,c.z };
	for (int i = 0; i < 9; i++) {
		m[i] = aux[i];
	}
}

inline Matrix3x3::Matrix3x3(const Matrix3x3& copy) {
	for (int i = 0; i < 9; i++) {
		m[i] = copy.m[i];
	}
}

inline Matrix3x3::~Matrix3x3() {
}

inline Matrix3x3 Matrix3x3::operator+(const Matrix3x3& other) const {
	float *aux;
	for (int i = 0; i < 9; i++) {
		*(aux + i) = m[i] + other.m[i];
	}
	return Matrix3x3(aux);
}

inline Matrix3x3& Matrix3x3::operator+=(const Matrix3x3& other) {
	for (int i = 0; i < 9; i++) {
		 m[i] += other.m[i];
	}
	return *this;
}

inline Matrix3x3 Matrix3x3::operator+(float value) const {
	float *aux;
	for (int i = 0; i < 9; i++) {
		*(aux + i) = m[i] + value;
	}
	return Matrix3x3(aux);
}

inline Matrix3x3& Matrix3x3::operator+=(float value) {
	for (int i = 0; i < 9; i++) {
		m[i] += value;
	}
	return *this;
}

inline Matrix3x3 Matrix3x3::operator-(const Matrix3x3& other) const {
	float *aux;
	for (int i = 0; i < 9; i++) {
		*(aux + i) = m[i] - other.m[i];
	}
	return Matrix3x3(aux);
}

inline Matrix3x3& Matrix3x3::operator-=(const Matrix3x3& other) {
	for (int i = 0; i < 9; i++) {
		m[i] -= other.m[i];
	}
	return *this;
}

inline Matrix3x3 Matrix3x3::operator-(float value) const {
	float *aux;
	for (int i = 0; i < 9; i++) {
		*(aux + i) = m[i] - value;
	}
	return Matrix3x3(aux);
}

inline Matrix3x3& Matrix3x3::operator-=(float value) {
	for (int i = 0; i < 9; i++) {
		m[i] -= value;
	}
	return *this;
}

inline Matrix3x3 Matrix3x3::operator*(float value) const {
	float *aux;
	for (int i = 0; i < 9; i++) {
		*(aux+i) = m[i] * value;
	}
	return Matrix3x3(aux);
}

inline Matrix3x3& Matrix3x3::operator*=(float value) {
	for (int i = 0; i < 9; i++) {
		m[i] *= value;
	}
	return *this;
}

inline Matrix3x3 Matrix3x3::operator/(float value) const {
	float *aux;
	for (int i = 0; i < 9; i++) {
		*(aux + i) = m[i] / value;
	}
	return Matrix3x3(aux);
}

inline Matrix3x3& Matrix3x3::operator/=(float value) {
	for (int i = 0; i < 9; i++) {
		m[i] /= value;
	}
	return *this;
}

inline bool Matrix3x3::operator==(const Matrix3x3& other) const {
	
	bool equal = true;

	for (int i = 0; i < 9 && equal; i++) {
		equal &= (m[i] == other.m[i]);
	}

	return equal;

}

inline bool Matrix3x3::operator!=(const Matrix3x3& other) const {
	bool notequal = true;

	for (int i = 0; i < 9 && notequal; i++) {
		notequal &= (m[i] != other.m[i]);
	}

	return notequal;
}

inline void Matrix3x3::operator=(const Matrix3x3& other) {
	for (int i = 0; i < 9; i++) {
		m[i] = other.m[i];
	}
}

inline Matrix3x3 Matrix3x3::Identity(){
	Vector3 a, b, c;
	a = { 1,0,0 };
	b = { 0,1,0 };
	c = { 0,0,1 };
	return Matrix3x3(a,b,c);
}

inline float Matrix3x3::Determinant() const {
	return m[0]*m[4]*m[8]+m[1]*m[5]*m[6]+m[2]*m[3]*m[7]-(m[2] * m[4] * m[6] + m[0] * m[5] * m[7] + m[1] * m[3] * m[8]);
}

inline bool Matrix3x3::GetInverse(Matrix3x3& out) const {
	if (this->Determinant() != 0) {

		Matrix3x3 res;
		res.operator=((Transpose().Adjoint()).operator/=(Determinant()));

		return true;
	}

	return false;
}

inline bool Matrix3x3::Inverse() {	
	if (this->Determinant() != 0){

		this->operator=((Transpose().Adjoint()).operator/=(Determinant()));

		return true;
	}

	return false;

}

inline Matrix3x3 Matrix3x3::Translate(const Vector2& mov_vector) {
	Vector3 a, b, c;
	a = { 1,0,mov_vector.x };
	b = { 0,1,mov_vector.y };
	c = { 0,0,1 };
	return Matrix3x3(a,b,c);
}

inline Matrix3x3 Matrix3x3::Translate(float x, float y) {
	Vector3 a, b, c;
	a = { 1,0,x };
	b = { 0,1,y };
	c = { 0,0,1 };
	return Matrix3x3(a, b, c);
}

inline Matrix3x3 Matrix3x3::Multiply(const Matrix3x3& other) const {
	Matrix3x3 result;
	Vector3 a, b;

	for (int i = 0; i < 9; i++) {

		if (i % 3 == 0) {
			b = { other.m[0],other.m[3],other.m[6] };
		}
		else {
			if (i % 3 == 1) {
				b = { other.m[1],other.m[4],other.m[7] };
			}
			else {
				b = { other.m[2],other.m[5],other.m[8] };
			}
		}
		if (i / 3 == 0) {
			a = { m[0],m[1],m[2] };
		}
		else {
			if (i / 3 == 1) {
				a = { m[3],m[4],m[5] };
			}
			else {
				a = { m[6],m[7],m[8] };
			}
		}

		result.m[i] = a.x*b.x + a.y*b.y + a.z*b.z;

	}

	return result;
}

inline Matrix3x3 Matrix3x3::Adjoint() const {
	
	Matrix3x3 res;
	
	res.operator=(*this);

	res.m[0] = m[4] * m[8] - m[5] * m[7];
	res.m[1] = -(m[3] * m[8] - m[5] * m[6]);
	res.m[2] = m[3] * m[7] - m[4] * m[6];

	res.m[3] = -(m[1] * m[8] - m[2] * m[7]);
	res.m[4] = m[0] * m[8] - m[2] * m[6];
	res.m[5] = -(m[0] * m[7] - m[1] * m[6]);

	res.m[6] = m[1] * m[5] - m[2] * m[4];
	res.m[7] = -(m[0] * m[5] - m[2] * m[3]);
	res.m[8] = m[0] * m[4] - m[1] * m[3];

	//res = res.Transpose(); jaja no soy muy listo, que rica horita me ha costado esto
	
	return res;
}

inline Matrix3x3 Matrix3x3::Transpose() const {
	Vector3 a, b, c;
	a = { m[0],m[3],m[6] };
	b = { m[1],m[4],m[7] };
	c = { m[2],m[5],m[8] };
	return Matrix3x3(a,b,c);
}

inline Vector3 Matrix3x3::GetColum(int colum) const {
	return Vector3(m[colum],m[colum+3],m[colum+6]);
}

inline Vector3 Matrix3x3::GetLine(int line) const {
	return Vector3(m[(line)*3], m[(line) * 3+1], m[((line) * 3+2)]);
}

#endif 