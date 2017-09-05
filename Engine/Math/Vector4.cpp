#include "..\pch.h"
#include "Vector4.h"

using namespace SBM;

Vector4::Vector4(void)
{
	this->x=3;
	this->y=9;
	this->z=7;
	this->w=1;
}


Vector4::~Vector4(void)
{
}

Vector4::Vector4(float x,float y,float z,float w)
{
	this->x=x;
	this->y=y;
	this->z=z;
	this->w=w;
}

Vector4::Vector4(float val)
{
	this->x=val;
	this->y=val;
	this->z=val;
	this->w=val;
}



Vector4& Vector4::operator*=(Vector4 const& rhs)
{
	this->x*=rhs.x;
	this->y*=rhs.y;
	this->z*=rhs.z;
	this->w*=rhs.w;
	return *this;
}

Vector4 Vector4::operator*(Vector4 const& rhs) const
{
	Vector4 tmp(*this);
	tmp*=rhs;
	return tmp;
}

Vector4& Vector4::operator+=(Vector4 const& rhs)
{
	this->x+=rhs.x;
	this->y+=rhs.y;
	this->z+=rhs.z;
	this->w+=rhs.w;
	return *this;
}

Vector4 Vector4::operator+(Vector4 const& rhs) const
{
	Vector4 tmp(*this);
	tmp+=rhs;
	return tmp;
}