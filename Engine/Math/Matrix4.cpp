#include "..\SBE_Internal.h"
#include "Matrix4.h"
using namespace SBM;

Matrix4::Matrix4(void)
{
	m[0] = 0;
	m[1] = 0;
	m[2] = 0;
	m[3] = 0;

	m[4] = 0;
	m[5] = 0;
	m[6] = 0;
	m[7] = 0;

	m[8] = 0;
	m[9] = 0;
	m[10] = 0;
	m[11] = 0;

	m[12] = 0;
	m[13] = 0;
	m[14] = 0;
	m[15] = 0;
}

Matrix4::Matrix4(float m00, float m01, float m02, float m03, float m04, float m05, float m06, float m07, float m08, float m09, float m10, float m11, float m12, float m13, float m14, float m15)
{
	m[0] = m00;
	m[1] = m01;
	m[2] = m02;
	m[3] = m03;

	m[4] = m04;
	m[5] = m05;
	m[6] = m06;
	m[7] = m07;

	m[8] = m08;
	m[9] = m09;
	m[10] = m10;
	m[11] = m11;

	m[12] = m12;
	m[13] = m13;
	m[14] = m14;
	m[15] = m15;
}

Matrix4::~Matrix4(void)
{
}

Matrix4& Matrix4::operator*=(Matrix4 const& rhs)
{
	Matrix4 a(*this);

	m[0] = a.m[0] * rhs.m[0] + a.m[4] * rhs.m[1] + a.m[8] * rhs.m[2] + a.m[12] * rhs.m[3];
	m[1] = a.m[1] * rhs.m[0] + a.m[5] * rhs.m[1] + a.m[9] * rhs.m[2] + a.m[13] * rhs.m[3];
	m[2] = a.m[2] * rhs.m[0] + a.m[6] * rhs.m[1] + a.m[10] * rhs.m[2] + a.m[14] * rhs.m[3];
	m[3] = a.m[3] * rhs.m[0] + a.m[7] * rhs.m[1] + a.m[11] * rhs.m[2] + a.m[15] * rhs.m[3];

	m[4] = a.m[0] * rhs.m[4] + a.m[4] * rhs.m[5] + a.m[8] * rhs.m[6] + a.m[12] * rhs.m[7];
	m[5] = a.m[1] * rhs.m[4] + a.m[5] * rhs.m[5] + a.m[9] * rhs.m[6] + a.m[13] * rhs.m[7];
	m[6] = a.m[2] * rhs.m[4] + a.m[6] * rhs.m[5] + a.m[10] * rhs.m[6] + a.m[14] * rhs.m[7];
	m[7] = a.m[3] * rhs.m[4] + a.m[7] * rhs.m[5] + a.m[11] * rhs.m[6] + a.m[15] * rhs.m[7];

	m[8] = a.m[0] * rhs.m[8] + a.m[4] * rhs.m[9] + a.m[8] * rhs.m[10] + a.m[12] * rhs.m[11];
	m[9] = a.m[1] * rhs.m[8] + a.m[5] * rhs.m[9] + a.m[9] * rhs.m[10] + a.m[13] * rhs.m[11];
	m[10] = a.m[2] * rhs.m[8] + a.m[6] * rhs.m[9] + a.m[10] * rhs.m[10] + a.m[14] * rhs.m[11];
	m[11] = a.m[3] * rhs.m[8] + a.m[7] * rhs.m[9] + a.m[11] * rhs.m[10] + a.m[15] * rhs.m[11];

	m[12] = a.m[0] * rhs.m[12] + a.m[4] * rhs.m[13] + a.m[8] * rhs.m[14] + a.m[12] * rhs.m[15];
	m[13] = a.m[1] * rhs.m[12] + a.m[5] * rhs.m[13] + a.m[9] * rhs.m[14] + a.m[13] * rhs.m[15];
	m[14] = a.m[2] * rhs.m[12] + a.m[6] * rhs.m[13] + a.m[10] * rhs.m[14] + a.m[14] * rhs.m[15];
	m[15] = a.m[3] * rhs.m[12] + a.m[7] * rhs.m[13] + a.m[11] * rhs.m[14] + a.m[15] * rhs.m[15];

	return *this;
}

Matrix4 Matrix4::operator*(Matrix4 const& rhs) const
{
	Matrix4 tmp(*this);
	tmp *= rhs;
	return tmp;
}

Vector3 Matrix4::operator*(Vector3 const& vec)
{
	Vector3 ret;
	ret.x = m[0] * vec.x + m[4] * vec.y + m[8] * vec.z + m[12];
	ret.y = m[1] * vec.x + m[5] * vec.y + m[9] * vec.z + m[13];
	ret.z = m[2] * vec.x + m[6] * vec.y + m[10] * vec.z + m[14];
	return ret;
}

float Matrix4::operator[](int i) const
{
	return m[i];
}

float& Matrix4::operator[](int i)
{
	return m[i];
}

void Matrix4::Set(Matrix4 const& mat)
{
	for (int i = 0; i < 16; i++)
	{
		m[0] = mat.m[0];
	}
}

void Matrix4::Inverse()
{
	Matrix4 tmp(
		m[0], m[4], m[8], m[12],
		m[1], m[5], m[9], m[13],
		m[2], m[6], m[10], m[14],
		m[3], m[7], m[11], m[15]);
	Set(tmp);
}

Matrix4 Matrix4::Inversed()
{
	Matrix4 tmp(
		m[0], m[4], m[8], m[12],
		m[1], m[5], m[9], m[13],
		m[2], m[6], m[10], m[14],
		m[3], m[7], m[11], m[15]);
	return tmp;
}

Matrix4 Matrix4::Identity()
{
	Matrix4 ret;
	ret.m[0] = 1;
	ret.m[5] = 1;
	ret.m[10] = 1;
	ret.m[15] = 1;
	return ret;
}

Matrix4 Matrix4::Translation(float x, float y, float z)
{
	Matrix4 ret;
	ret.m[0] = 1;
	ret.m[5] = 1;
	ret.m[10] = 1;
	ret.m[12] = x;
	ret.m[13] = y;
	ret.m[14] = z;
	ret.m[15] = 1;
	return ret;
}

Matrix4 Matrix4::Scale(float x, float y, float z)
{
	Matrix4 ret;
	ret.m[0] = x;
	ret.m[5] = y;
	ret.m[10] = z;
	ret.m[15] = 1;
	return ret;
}

Matrix4 Matrix4::RotationX(float alpha)
{
	Matrix4 ret;
	ret.m[0] = 1;
	ret.m[5] = cosf(alpha);
	ret.m[6] = -sinf(alpha);
	ret.m[9] = sinf(alpha);
	ret.m[10] = cosf(alpha);
	ret.m[15] = 1;
	return ret;
}

Matrix4 Matrix4::RotationY(float beta)
{
	Matrix4 ret;
	ret.m[0] = (float)cos(beta);
	ret.m[2] = (float)sin(beta);
	ret.m[5] = 1;
	ret.m[8] = (float)-sin(beta);
	ret.m[10] = (float)cos(beta);
	ret.m[15] = 1;
	return ret;
}

Matrix4 Matrix4::RotationZ(float gamma)
{
	Matrix4 ret;
	ret.m[0] = (float)cos(gamma);
	ret.m[1] = (float)-sin(gamma);
	ret.m[4] = (float)sin(gamma);
	ret.m[5] = (float)cos(gamma);
	ret.m[10] = 1;
	ret.m[15] = 1;
	return ret;
}

Matrix4 Matrix4::Rotation(float x, float y, float z)
{
	return RotationX(x)* RotationY(y)*RotationZ(z);
}

Matrix4 Matrix4::LookAt(Vector3 const& pos, Vector3 const& target, Vector3 const& up)
{
	Vector3 vz = pos - target;
	vz.Normalise();

	Vector3 vx = Vector3::Cross(up, vz);
	vx.Normalise();

	Vector3 vy = Vector3::Cross(vz, vx);

	Matrix4 mat = Matrix4(vx.x, vy.x, vz.x, 0.0f,
		vx.y, vy.y, vz.y, 0.0f,
		vx.z, vy.z, vz.z, 0.0f,
		Vector3::Dot(vx, -pos), Vector3::Dot(vy, -pos), Vector3::Dot(vz, -pos), 1);
	return mat;
}

Matrix4 Matrix4::LookAt(float eye_x, float eye_y, float eye_z, float lookAt_X, float lookAt_Y, float lookAt_Z, float up_X, float up_Y, float up_Z)
{
	return LookAt(Vector3(eye_x, eye_y, eye_z), Vector3(lookAt_X, lookAt_Y, lookAt_Z), Vector3(up_X, up_Y, up_Z));
}

Matrix4 Matrix4::Perspective(float fov, float aspect, float nearr, float farr)
{
	Matrix4 ret;

	float h = 1.0f / tanf(float(fov *0.5* M_PI / 180.0f));
	float neg_depth = nearr - farr;

	ret.m[0] = h / aspect;
	ret.m[5] = h;
	ret.m[10] = (farr + nearr) / neg_depth;
	ret.m[11] = -1;
	ret.m[14] = 2.0f*(nearr*farr) / neg_depth;

	return ret;
}

Matrix4 Matrix4::Ortho(float left, float right, float bottom, float top, float nearr, float farr)
{
	Matrix4 ret;

	ret[0] = 2 / (right - left);

	ret[5] = 2 / (top - bottom);

	ret[10] = -2 / (farr - nearr);

	ret[12] = -(right + left) / (right - left);
	ret[13] = -(top + bottom) / (top - bottom);
	ret[14] = -(farr + nearr) / (farr - nearr);
	ret[15] = 1;

	return ret;
}