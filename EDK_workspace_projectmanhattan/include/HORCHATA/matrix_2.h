#ifndef __MATRIX2_H__
#define __MATRIX2_H__ 1

#include "vector_2.h"

class Matrix2x2 {
public:

	Matrix2x2();
	Matrix2x2(float a[4]);
	Matrix2x2(float value);
	Matrix2x2(const Vector2& a, const Vector2& b); 
	Matrix2x2(const Matrix2x2& copy);
	~Matrix2x2();
	Matrix2x2 Identity() const;
	Matrix2x2 Multiply(const Matrix2x2& other) const;
	float Determinant() const;
	Matrix2x2 Adjoint() const;
	Vector2 GetLine(int line) const;
	Vector2 GetColum(int line) const;

	Matrix2x2 Inverse() const;
	Matrix2x2 Transpose() const;

	inline Matrix2x2 operator+(const Matrix2x2& other) const;
	inline void operator+=(const Matrix2x2& other);
	inline Matrix2x2 operator+(float value) const;
	inline void operator+=(float value);
	inline Matrix2x2 operator-(const Matrix2x2& other) const;
	inline void operator-=(const Matrix2x2& other);
	inline Matrix2x2 operator-(float value) const;
	inline void operator-=(float value);

	inline Matrix2x2 operator*(float value) const;
	inline void operator*=(float value);
	inline Matrix2x2 operator/(float value) const;
	inline void operator/=(float value);

	bool operator==(const Matrix2x2& other) const;
	bool operator!=(const Matrix2x2& other) const;
	inline void operator=(const Matrix2x2& other);

	float m[4];
};


inline Matrix2x2::Matrix2x2() {
}

inline Matrix2x2::Matrix2x2(float a[4]) {
	for (int i = 0; i < 4; i++) {
		m[i] = a[i];
	}
}

inline Matrix2x2::Matrix2x2(float a) {
	for (int i = 0; i < 4; i++) {
		m[i] = a;
	}
}

inline Matrix2x2::Matrix2x2(const Vector2& a, const Vector2& b) {
	m[0] = a.x;
	m[1] = a.y;
	m[2] = b.x;
	m[3] = b.y;
}

inline Matrix2x2::Matrix2x2(const Matrix2x2& copy) {
	for (int i = 0; i < 4; i++) {
		m[i] = copy.m[i];
	}
}

inline Matrix2x2::~Matrix2x2() {

}

inline Matrix2x2 Matrix2x2::operator+(const Matrix2x2& other) const {
	float values[4];
	for (int i = 0; i < 4; i++) {
		values[i] = m[i] + other.m[i];
	}
	return Matrix2x2(values);
}

inline void Matrix2x2::operator+=(const Matrix2x2& other) {
	for (int i = 0; i < 4; i++) {
		m[i] += other.m[i];
	}
}

inline Matrix2x2 Matrix2x2::operator+(float value) const {
	float values[4];
	for (int i = 0; i < 4; i++) {
		values[i] = m[i] + value;
	}
	return Matrix2x2(values);
}

inline void Matrix2x2::operator+=(float value) {
	for (int i = 0; i < 4; i++) {
		m[i] += value;
	}
}

inline Matrix2x2 Matrix2x2::operator-(const Matrix2x2& other) const {
	float values[4];
	for (int i = 0; i < 4; i++) {
		values[i] = m[i] - other.m[i];
	}
	return Matrix2x2(values);
}

inline void Matrix2x2::operator-=(const Matrix2x2& other) {
	for (int i = 0; i < 4; i++) {
		m[i] -= other.m[i];
	}
}

inline Matrix2x2 Matrix2x2::operator-(float value) const {	
	float values[4];
	for (int i = 0; i < 4; i++) {
		values[i] = m[i] - value;
	}
	return Matrix2x2(values);
}

inline void Matrix2x2::operator-=(float value) {
	for (int i = 0; i < 4; i++) {
		m[i] -= value;
	}
}


inline Matrix2x2 Matrix2x2::operator*(float value) const {
	return Matrix2x2();
}

inline void Matrix2x2::operator*=(float value) {
}

inline Matrix2x2 Matrix2x2::operator/(float value) const {
	return Matrix2x2();
}

inline void Matrix2x2::operator/=(float value) {
}


inline bool Matrix2x2::operator==(const Matrix2x2& other) const {
	return true;
}

inline bool Matrix2x2::operator!=(const Matrix2x2& other) const {
	return true;
}

inline void Matrix2x2::operator=(const Matrix2x2& other) {
}

inline Matrix2x2 Matrix2x2::Identity() const {
	return Matrix2x2();
}

inline float Matrix2x2::Determinant() const {
	return 0.0f;
}

inline Matrix2x2 Matrix2x2::Inverse() const {
	return Matrix2x2();
}

inline Matrix2x2 Matrix2x2::Multiply(const Matrix2x2& other) const {
	return Matrix2x2();
}

inline Matrix2x2 Matrix2x2::Adjoint() const {
	return Matrix2x2();
}

inline Matrix2x2 Matrix2x2::Transpose() const {
	return Matrix2x2();
}

inline Vector2 Matrix2x2::GetLine(int line) const {
	return Vector2();
}

inline Vector2 Matrix2x2::GetColum(int line) const {	
	return Vector2();
}


#endif
