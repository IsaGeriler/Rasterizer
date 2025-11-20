#pragma once
#define _USE_MATH_DEFINES
#define SQ(x) (x * x)

#include <algorithm>
#include <cmath>
#include <iostream>

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