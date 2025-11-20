#pragma once
#define _USE_MATH_DEFINES
#define SQ(x) (x * x)

#include <algorithm>
#include <cmath>
#include <iostream>

// Linear Interpolation
template<typename Type>
static Type lerp(const Type a, const Type b, float t) {
	return a * (1.f - t) + (b * t);
}

// Vec3 Class
class Vec3 {
public:
	// Union elements can be accessed in the same memory address, unlike structs
	union {
		float v[3];
		struct { float x, y, z; };
	};

	// Constructors
	Vec3() : x(0.f), y(0.f), z(0.f) {}
	Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

	// Vec3 Operator Overloading
	Vec3 operator+(const Vec3& pVec) const { return Vec3(v[0] + pVec.v[0], v[1] + pVec.v[1], v[2] + pVec.v[2]); }
	Vec3 operator-(const Vec3& pVec) const { return Vec3(v[0] - pVec.v[0], v[1] - pVec.v[1], v[2] - pVec.v[2]); }
	Vec3 operator*(const Vec3& pVec) const { return Vec3(v[0] * pVec.v[0], v[1] * pVec.v[1], v[2] * pVec.v[2]); }
	Vec3 operator/(const Vec3& pVec) const { return Vec3(v[0] / pVec.v[0], v[1] / pVec.v[1], v[2] / pVec.v[2]); }

	Vec3 operator*(const float scalar) const { return Vec3(v[0] * scalar, v[1] * scalar, v[2] * scalar); }
	Vec3 operator/(const float scalar) const { return Vec3(v[0] / scalar, v[1] / scalar, v[2] / scalar); }

	// Vec3& Operator Overloading
	Vec3& operator+=(const Vec3& pVec) {
		v[0] += pVec.v[0]; v[1] += pVec.v[1]; v[2] += pVec.v[2];
		return *this;
	}

	Vec3& operator-=(const Vec3& pVec) {
		v[0] -= pVec.v[0]; v[1] -= pVec.v[1]; v[2] -= pVec.v[2];
		return *this;
	}

	Vec3& operator*=(const Vec3& pVec) {
		v[0] *= pVec.v[0]; v[1] *= pVec.v[1]; v[2] *= pVec.v[2];
		return *this;
	}

	Vec3& operator/=(const Vec3& pVec) {
		v[0] /= pVec.v[0]; v[1] /= pVec.v[1]; v[2] /= pVec.v[2];
		return *this;
	}

	Vec3& operator*=(const float scalar) {
		v[0] *= scalar; v[1] *= scalar; v[2] *= scalar;
		return *this;
	}

	Vec3& operator/=(const float scalar) {
		v[0] /= scalar; v[1] /= scalar; v[2] /= scalar;
		return *this;
	}

	// Unary Negate
	Vec3 operator-() const { return Vec3(-v[0], -v[1], -v[2]); }

	// Methods
	// Length (magnitude) of a vector
	float length() const { return sqrt(SQ(v[0]) + SQ(v[1]) + SQ(v[2])); }
	float lengthSquare() const { return SQ(v[0]) + SQ(v[1]) + SQ(v[2]); }

	// Normalize a vector (i.e. unit vector)
	Vec3 normalize() {
		float len = 1.f / sqrt(SQ(v[0]) + SQ(v[1]) + SQ(v[2]));
		return Vec3(v[0] * len, v[1] * len, v[2] * len);
	}

	float normalizeAndGetLength() {
		float length = sqrt(SQ(v[0]) + SQ(v[1]) + SQ(v[2]));
		float len = 1.f / length;
		v[0] *= len; v[1] *= len; v[2] *= len;
		return length;
	}

	// Dot & Cross Products
	float Dot(const Vec3& pVec) const { return (v[0] * pVec.v[0] + v[1] * pVec.v[1] + v[2] * pVec.v[2]); }
	Vec3 Cross(const Vec3& pVec) { return Vec3((v[1] * pVec.v[2] - v[2] * pVec.v[1]), (v[2] * pVec.v[0] - v[0] * pVec.v[2]), (v[0] * pVec.v[1] - v[1] * pVec.v[0])); }
	
	// Print
	void print() const { std::cout << '<' << v[0] << ", " << v[1] << ", " << v[2] << '>' << std::endl; }

	// Max and Min of Vector Components
	float max() const { return std::max(x, std::max(y, z)); }
	float min() const { return std::min(x, std::min(y, z)); }
};

float Dot(const Vec3& v1, const Vec3& v2) { return (v1.v[0] * v2.v[0] + v1.v[1] * v2.v[1] + v1.v[2] * v2.v[2]); }
Vec3 Cross(const Vec3& v1, const Vec3& v2) { return Vec3((v1.v[1] * v2.v[2] - v1.v[2] * v2.v[1]), (v1.v[2] * v2.v[0] - v1.v[0] * v2.v[2]), (v1.v[0] * v2.v[1] - v1.v[1] * v2.v[0])); }
Vec3 Max(const Vec3& v1, const Vec3& v2) { return Vec3(std::max(v1.v[0], v2.v[0]), std::max(v1.v[1], v2.v[1]), std::max(v1.v[2], v2.v[2])); }
Vec3 Min(const Vec3& v1, const Vec3& v2) { return Vec3(std::min(v1.v[0], v2.v[0]), std::min(v1.v[1], v2.v[1]), std::min(v1.v[2], v2.v[2])); }

// Vec4 Class
class Vec4 {
public:
	// Union elements can be accessed in the same memory address, unlike structs
	union {
		float v[4];
		struct { float x, y, z, w; };
	};

	// Constructors
	Vec4() : x(0.f), y(0.f), z(0.f), w(0.f) {}
	Vec4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}

	// Vec4 Operator Overloading
	Vec4 operator+(const Vec4& pVec) const { return Vec4(v[0] + pVec.v[0], v[1] + pVec.v[1], v[2] + pVec.v[2], v[3] + pVec.v[3]); }
	Vec4 operator-(const Vec4& pVec) const { return Vec4(v[0] - pVec.v[0], v[1] - pVec.v[1], v[2] - pVec.v[2], v[3] - pVec.v[3]); }
	Vec4 operator*(const Vec4& pVec) const { return Vec4(v[0] * pVec.v[0], v[1] * pVec.v[1], v[2] * pVec.v[2], v[3] * pVec.v[3]); }
	Vec4 operator/(const Vec4& pVec) const { return Vec4(v[0] / pVec.v[0], v[1] / pVec.v[1], v[2] / pVec.v[2], v[3] / pVec.v[3]); }

	Vec4 operator*(const float scalar) const { return Vec4(v[0] * scalar, v[1] * scalar, v[2] * scalar, v[3] * scalar); }
	Vec4 operator/(const float scalar) const { return Vec4(v[0] / scalar, v[1] / scalar, v[2] / scalar, v[3] / scalar); }

	// Vec4& Operator Overloading
	Vec4& operator+=(const Vec4& pVec) {
		v[0] += pVec.v[0]; v[1] += pVec.v[1]; v[2] += pVec.v[2]; v[3] += pVec.v[3];
		return *this;
	}

	Vec4& operator-=(const Vec4& pVec) {
		v[0] -= pVec.v[0]; v[1] -= pVec.v[1]; v[2] -= pVec.v[2]; v[3] -= pVec.v[3];
		return *this;
	}

	Vec4& operator*=(const Vec4& pVec) {
		v[0] *= pVec.v[0]; v[1] *= pVec.v[1]; v[2] *= pVec.v[2]; v[3] *= pVec.v[3];
		return *this;
	}

	Vec4& operator/=(const Vec4& pVec) {
		v[0] /= pVec.v[0]; v[1] /= pVec.v[1]; v[2] /= pVec.v[2]; v[3] /= pVec.v[3];
		return *this;
	}

	Vec4& operator*=(const float scalar) {
		v[0] *= scalar; v[1] *= scalar; v[2] *= scalar; v[3] *= scalar;
		return *this;
	}

	Vec4& operator/=(const float scalar) {
		v[0] /= scalar; v[1] /= scalar; v[2] /= scalar; v[3] /= scalar;
		return *this;
	}

	// Unary Negate
	Vec4 operator-() const { return Vec4(-v[0], -v[1], -v[2], -v[3]); }

	// Methods
	// Length (magnitude) of a vector
	float length() const { return sqrt(SQ(v[0]) + SQ(v[1]) + SQ(v[2]) + SQ(v[3])); }
	float lengthSquare() const { return SQ(v[0]) + SQ(v[1]) + SQ(v[2]) + SQ(v[3]); }

	// Normalize a vector (i.e. unit vector)
	Vec4 normalize() {
		float len = 1.f / sqrt(SQ(v[0]) + SQ(v[1]) + SQ(v[2]) + SQ(v[3]));
		return Vec4(v[0] * len, v[1] * len, v[2] * len, v[3] * len);
	}

	float normalizeAndGetLength() {
		float length = sqrt(SQ(v[0]) + SQ(v[1]) + SQ(v[2]));
		float len = 1.f / length;
		v[0] *= len; v[1] *= len; v[2] *= len; v[3] *= len;
		return length;
	}

	// Dot Product
	float Dot(const Vec4& pVec) const { return (v[0] * pVec.v[0] + v[1] * pVec.v[1] + v[2] * pVec.v[2] + v[3] * pVec.v[3]); }
	
	// Print
	void print() const { std::cout << '<' << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << '>' << std::endl; }

	// Max and Min of Vector Components
	float max() const { return std::max(std::max(x, y), std::max(y, z)); }
	float min() const { return std::min(std::min(x, y), std::min(y, z)); }
};

float Dot(const Vec4& v1, const Vec4& v2) { return (v1.v[0] * v2.v[0] + v1.v[1] * v2.v[1] + v1.v[2] * v2.v[2] + v1.v[3] * v2.v[3]); }
Vec4 Max(const Vec4& v1, const Vec4& v2) { return Vec4(std::max(v1.v[0], v2.v[0]), std::max(v1.v[1], v2.v[1]), std::max(v1.v[2], v2.v[2]), std::max(v1.v[3], v2.v[3])); }
Vec4 Min(const Vec4& v1, const Vec4& v2) { return Vec4(std::min(v1.v[0], v2.v[0]), std::min(v1.v[1], v2.v[1]), std::min(v1.v[2], v2.v[2]), std::min(v1.v[3], v2.v[3])); }

// 4x4 Matrix Class
class Matrix {
public:
	// Union elements can be accessed in the same memory address, unlike structs
	union {
		float a[4][4];
		float m[16];
	};

	// Constructors
	Matrix() {
		// Initialize to identity matrix
		for (int i = 0; i < 16; i++) (i % 5 == 0) ? m[i] = 1 : m[i] = 0;
	}

	Matrix(float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8,
		   float f9, float f10, float f11, float f12, float f13, float f14, float f15, float f16) {
		// Initialize for 16 floating values
		m[0] = f1; m[1] = f2; m[2] = f3; m[3] = f4;
		m[4] = f5; m[5] = f6; m[6] = f7; m[7] = f8;
		m[8] = f9; m[9] = f10; m[10] = f11; m[11] = f12;
		m[12] = f13; m[13] = f14; m[14] = f15; m[15] = f16;
	}

	// Operator Overloading
	float& operator[](const int index) { return m[index]; }

	// Methods
	// Identity Matrix
	Matrix identity() {
		Matrix iden;
		for (int i = 0; i < 16; i++) (i % 5 == 0) ? iden[i] = 1 : iden[i] = 0;
		return iden;
	}

	// Matrix & Vector Multiplication
	Vec4 mul(const Vec4& v) {
		return Vec4((v.x * m[0] + v.y * m[1] + v.z * m[2] + v.w * m[3]),
					(v.x * m[4] + v.y * m[5] + v.z * m[6] + v.w * m[7]),
					(v.x * m[8] + v.y * m[9] + v.z * m[10] + v.w * m[11]),
					(v.x * m[12] + v.y * m[13] + v.z * m[14] + v.w * m[15]));
	}

	Vec3 mulPoint(const Vec3& v) {
		// w = 1
		return Vec3((v.x * m[0] + v.y * m[1] + v.z * m[2]) + m[3],
					(v.x * m[4] + v.y * m[5] + v.z * m[6]) + m[7],
					(v.x * m[8] + v.y * m[9] + v.z * m[10]) + m[11]);
	}

	Vec3 mulVec(const Vec3& v) {
		// w = 0
		return Vec3((v.x * m[0] + v.y * m[1] + v.z * m[2]),
					(v.x * m[4] + v.y * m[5] + v.z * m[6]),
					(v.x * m[8] + v.y * m[9] + v.z * m[10]));
	}

	// 4x4 Matrix Multiplication
	Matrix mul(const Matrix& matrix) const {
		Matrix ret;
		ret.m[0] = m[0] * matrix.m[0] + m[1] * matrix.m[4] + m[2] * matrix.m[8] + m[3] * matrix.m[12];
		ret.m[1] = m[0] * matrix.m[1] + m[1] * matrix.m[5] + m[2] * matrix.m[9] + m[3] * matrix.m[13];
		ret.m[2] = m[0] * matrix.m[2] + m[1] * matrix.m[6] + m[2] * matrix.m[10] + m[3] * matrix.m[14];
		ret.m[3] = m[0] * matrix.m[3] + m[1] * matrix.m[7] + m[2] * matrix.m[11] + m[3] * matrix.m[15];
		ret.m[4] = m[4] * matrix.m[0] + m[5] * matrix.m[4] + m[6] * matrix.m[8] + m[7] * matrix.m[12];
		ret.m[5] = m[4] * matrix.m[1] + m[5] * matrix.m[5] + m[6] * matrix.m[9] + m[7] * matrix.m[13];
		ret.m[6] = m[4] * matrix.m[2] + m[5] * matrix.m[6] + m[6] * matrix.m[10] + m[7] * matrix.m[14];
		ret.m[7] = m[4] * matrix.m[3] + m[5] * matrix.m[7] + m[6] * matrix.m[11] + m[7] * matrix.m[15];
		ret.m[8] = m[8] * matrix.m[0] + m[9] * matrix.m[4] + m[10] * matrix.m[8] + m[11] * matrix.m[12];
		ret.m[9] = m[8] * matrix.m[1] + m[9] * matrix.m[5] + m[10] * matrix.m[9] + m[11] * matrix.m[13];
		ret.m[10] = m[8] * matrix.m[2] + m[9] * matrix.m[6] + m[10] * matrix.m[10] + m[11] * matrix.m[14];
		ret.m[11] = m[8] * matrix.m[3] + m[9] * matrix.m[7] + m[10] * matrix.m[11] + m[11] * matrix.m[15];
		ret.m[12] = m[12] * matrix.m[0] + m[13] * matrix.m[4] + m[14] * matrix.m[8] + m[15] * matrix.m[12];
		ret.m[13] = m[12] * matrix.m[1] + m[13] * matrix.m[5] + m[14] * matrix.m[9] + m[15] * matrix.m[13];
		ret.m[14] = m[12] * matrix.m[2] + m[13] * matrix.m[6] + m[14] * matrix.m[10] + m[15] * matrix.m[14];
		ret.m[15] = m[12] * matrix.m[3] + m[13] * matrix.m[7] + m[14] * matrix.m[11] + m[15] * matrix.m[15];
		return ret;
	}

	// Rotate on x-axis
	Matrix rotateOnXAxis(const float theta) {
		Matrix xMat;
		xMat[0] = 1; xMat[1] = 0; xMat[2] = 0; xMat[3] = 0;
		xMat[4] = 0; xMat[5] = cos(theta); xMat[6] = -sin(theta); xMat[7] = 0;
		xMat[8] = 0; xMat[9] = sin(theta); xMat[10] = cos(theta); xMat[11] = 0;
		xMat[12] = 0; xMat[13] = 0; xMat[14] = 0; xMat[15] = 1;
		return xMat;
	}

	// Rotate on y-axis
	Matrix rotateOnYAxis(const float theta) {
		Matrix yMat;
		yMat[0] = cos(theta); yMat[1] = 0; yMat[2] = sin(theta); yMat[3] = 0;
		yMat[4] = 0; yMat[5] = 1; yMat[6] = 0; yMat[7] = 0;
		yMat[8] = -sin(theta); yMat[9] = 0; yMat[10] = cos(theta); yMat[11] = 0;
		yMat[12] = 0; yMat[13] = 0; yMat[14] = 0; yMat[15] = 1;
		return yMat;
	}
	
	// Rotate on z-axis
	Matrix rotateOnZAxis(const float theta) {
		Matrix zMat;
		zMat[0] = cos(theta); zMat[1] = -sin(theta); zMat[2] = 0; zMat[3] = 0;
		zMat[4] = sin(theta); zMat[5] = cos(theta); zMat[6] = 0; zMat[7] = 0;
		zMat[8] = 0; zMat[9] = 0; zMat[10] = 1; zMat[11] = 0;
		zMat[12] = 0; zMat[13] = 0; zMat[14] = 0; zMat[15] = 1;
		return zMat;
	}

	// Translate
	Matrix translate(const float t) {
		Matrix trans;
		trans[0] = 1; trans[1] = 0; trans[2] = 0; trans[3] = t;
		trans[4] = 0; trans[5] = 1; trans[6] = 0; trans[7] = t;
		trans[8] = 0; trans[9] = 0; trans[10] = 1; trans[11] = t;
		trans[12] = 0; trans[13] = 0; trans[14] = 0; trans[15] = 1;
		return trans;
	}

	// Scale
	Matrix scale(const float s) {
		Matrix sc;
		sc[0] = s; sc[1] = 0; sc[2] = 0; sc[3] = 0;
		sc[4] = 0; sc[5] = s; sc[6] = 0; sc[7] = 0;
		sc[8] = 0; sc[9] = 0; sc[10] = s; sc[11] = 0;
		sc[12] = 0; sc[13] = 0; sc[14] = 0; sc[15] = 1;
		return sc;
	}

	// Natural Acces for Matrix Multiplication (Operator Overloading)
	Matrix operator* (const Matrix& matrix) { return mul(matrix); }

	// Transpose
	Matrix& transpose() {
		for (int i = 0; i < 4; i++)
			for (int j = i + 1; j < 4; j++)
				std::swap(a[i][j], a[j][i]);
		return *this;
	}

	// Inverse of a matrix
	Matrix invert() {
		Matrix inv;
		inv[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
		inv[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
		inv[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];
		inv[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];
		inv[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
		inv[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
		inv[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];
		inv[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];
		inv[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6];
		inv[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] - m[12] * m[2] * m[7] + m[12] * m[3] * m[6];
		inv[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] + m[12] * m[1] * m[7] - m[12] * m[3] * m[5];
		inv[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] - m[12] * m[1] * m[6] + m[12] * m[2] * m[5];
		inv[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] - m[9] * m[2] * m[7] + m[9] * m[3] * m[6];
		inv[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] + m[8] * m[2] * m[7] - m[8] * m[3] * m[6];
		inv[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[9] - m[8] * m[1] * m[7] + m[8] * m[3] * m[5];
		inv[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[9] + m[8] * m[1] * m[6] - m[8] * m[2] * m[5];
		float det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

		if (det == 0) {
			// Handle this case
			std::cout << "det(M) = 0 [This matrix doesn't have an inverse... returning identity matrix for graceful termination]" << std::endl;
			return identity();
		}

		det = 1.0 / det;
		for (int i = 0; i < 16; i++)
			inv[i] = inv[i] * det;
		return inv;
	}
};

// Spherical Coordinate Class
class SphericalCoordinate {
public:
	// Union elements can be accessed in the same memory address, unlike structs
	union {
		float sc[3];
		struct { float phi, theta, r; };
	};

	// Constructors
	SphericalCoordinate() : phi(0.f), theta(0.f), r(1.f) {}
	SphericalCoordinate(float _phi, float _theta) : phi(_phi), theta(_theta), r(1.f) {}
	SphericalCoordinate(float _phi, float _theta, float _r) : phi(_phi), theta(_theta), r(_r) {}

	// Methods
	// Shading (Z-Up) - Convert from Cartesian
	SphericalCoordinate zUpFromCartesian(const Vec3& cartesian) {
		if (cartesian.lengthSquare() == 0) return SphericalCoordinate();
		theta = acos(cartesian.z / r);
		phi = atan2f(cartesian.y, cartesian.x);
		return SphericalCoordinate(phi, theta);
	}

	// Camera (Y-Up) - Convert from Cartesian
	SphericalCoordinate yUpFromCartesian(const Vec3& cartesian) {
		if (cartesian.lengthSquare() == 0) return SphericalCoordinate();
		theta = acos(cartesian.y / r);
		phi = atan2f(cartesian.z, cartesian.x);
		return SphericalCoordinate(phi, theta);
	}

	// Shading (Z-Up) - Convert to Cartesian
	Vec3 zUpToCartesian() { return Vec3(r * sin(theta) * cos(phi), r * sin(theta) * sin(phi), r * cos(theta)); }

	// Camera (Y-Up) - Convert to Cartesian
	Vec3 yUpToCartesian() { return Vec3(r * sin(theta) * cos(phi), r * cos(theta), r * sin(theta) * sin(phi)); }

	// Calculate theta and phi w.r.t. shading (z-up) and camera (y-up)
	float zUpCalculateTheta(const Vec3& cartesian) const { return acos(cartesian.z / r); }
	float yUpCalculateTheta(const Vec3& cartesian) const { return acos(cartesian.y / r); }
	float zUpCalculatePhi(const Vec3& cartesian) const { return atan2f(cartesian.y, cartesian.x); }
	float yUpCalculatePhi(const Vec3& cartesian)  const { return atan2f(cartesian.z, cartesian.x); }
};

// Quaternion Class
class Quaternion {
public:
	// Union elements can be accessed in the same memory address, unlike structs
	union {
		// Quaternion Form = d + ai + bj + ck
		float q[4];
		struct { float d, a, b, c; }; 
	};

	// Constructors
	Quaternion() : d(0.f), a(0.f), b(0.f), c(0.f) {}
	Quaternion(float _d, float _a, float _b, float _c) : d(_d), a(_a), b(_b), c(_c) {}

	// Methods
	// Magnitude
	float magnitude() const { return sqrt(SQ(a) + SQ(b) + SQ(c) + SQ(d)); }

	// Normalize
	Quaternion normalize() {
		float mag = sqrt(SQ(a) + SQ(b) + SQ(c) + SQ(d));
		mag = 1.f / mag;
		return Quaternion(d / mag, a / mag, b / mag, c / mag);
	}

	// Conjugate
	Quaternion conjugate() { return Quaternion(d, -a, -b, -c); }

	// Inverse
	Quaternion inverse() {
		float mag = sqrt(SQ(a) + SQ(b) + SQ(c) + SQ(d));
		mag = 1.f / mag;
		Quaternion conj = conjugate();
		return Quaternion(conj.d / mag, conj.a / mag, conj.b / mag, conj.c / mag);
	}

	// Multiply
	Quaternion multiply(const Quaternion& q2) {
		return Quaternion((d * q2.d - a * q2.a - b * q2.b - c * q2.c),
						  (d * q2.a + a * q2.d + b * q2.c - c * q2.b),
						  (d * q2.b - a * q2.c + b * q2.d + c * q2.a),
						  (d * q2.c + a * q2.b - b * q2.a + c * q2.d));
	}

	// Construct a Quaternion from axis-angle
	Quaternion fromAxisAngle(const Vec3& pVec, const float theta) {
		return Quaternion(cos(theta / 2), pVec.x * sin(theta / 2), pVec.y * sin(theta / 2), pVec.z * sin(theta / 2));
	}

	// Quaternion to Matrix
	Matrix toMatrix() const {
		Matrix m;
		float aa = a * a, ab = a * b, ac = a * c;
		float bb = b * b, bc = b * c, cc = c * c;
		float da = d * a, db = d * b, dc = d * c;
		
		m[0] = 1 - 2 * (bb + cc); m[1] = 2 * (ab - dc); m[2] = 2 * (ac + db); m[3] = 0;
		m[4] = 2 * (ab + dc); m[5] = 1 - 2 * (aa + cc); m[6] = 2 * (bc - da); m[7] = 0;
		m[8] = 2 * (ac - db); m[9] = 2 * (bc + da); m[10] = 1 - 2 * (aa + bb); m[11] = 0;
		m[12] = m[13] = m[14] = 0; m[15] = 1;
		return m;
	}
};

Quaternion multiply(const Quaternion& q1, const Quaternion& q2) {
	return Quaternion((q1.d * q2.d - q1.a * q2.a - q1.b * q2.b - q1.c * q2.c),
					  (q1.d * q2.a + q1.a * q2.d + q1.b * q2.c - q1.c * q2.b),
					  (q1.d * q2.b - q1.a * q2.c + q1.b * q2.d + q1.c * q2.a),
					  (q1.d * q2.c + q1.a * q2.b - q1.b * q2.a + q1.c * q2.d));
}

// Colour Class
class Colour {
public:
	// Union elements can be accessed in the same memory address, unlike structs
	union {
		float c[4];
		struct { float r, g, b, a; };
	};

	// Constructors
	Colour(float _r, float _g, float _b) : r(_r), g(_g), b(_b), a(1.f) {}
	Colour(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a) {}
	Colour(unsigned char _r, unsigned char _g, unsigned char _b) : r(_r / 255.f), g(_g / 255.f), b(_b / 255.f), a(1.f) {}
	Colour(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a) : r(_r / 255.f), g(_g / 255.f), b(_b / 255.f), a(_a / 255.f) {}
};