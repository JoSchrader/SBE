#include "..\pch.h"
#include "Vector3.h"

using namespace SBM;

Vector3::Vector3(void)
{
	x=0;
	y=0;
	z=0;
}

Vector3::Vector3(float x,float y,float z)
{
	this->x=x;
	this->y=y;
	this->z=z;
}

Vector3::Vector3(float val)
{
	this->x=val;
	this->y=val;
	this->z=val;
}

Vector3::~Vector3(void)
{
}

Vector3 Vector3::Cross( Vector3 const& vec1, Vector3 const&  vec2)
{
	return Vector3( vec1.y* vec2.z-vec1.z*vec2.y, 
					vec1.z* vec2.x-vec1.x*vec2.z, 
					vec1.x* vec2.y-vec1.y*vec2.x);
}

float Vector3::Dot( Vector3 const& vec1, Vector3 const& vec2)
{
	return	vec1.x*vec2.x+vec1.y*vec2.y+vec1.z*vec2.z;
}

Vector3& Vector3::operator+=(const Vector3& rhs)
{
	this->x+=rhs.x;
	this->y+=rhs.y;
	this->z+=rhs.z;
	return *this;
}

Vector3 Vector3::operator+(Vector3 const& rhs) const
{
	Vector3 tmp(*this);
	tmp+=rhs;
	return tmp;
}

Vector3& Vector3::operator-=(Vector3 const& rhs)
{
	this->x-=rhs.x;
	this->y-=rhs.y;
	this->z-=rhs.z;
	return *this;
}

Vector3 Vector3::operator-(Vector3 const& rhs) const
{
	Vector3 tmp(*this);
	tmp-=rhs;
	return tmp;
}

Vector3& Vector3::operator*=(Vector3 const& rhs)
{
	this->x*=rhs.x;
	this->y*=rhs.y;
	this->z*=rhs.z;
	return *this;
}

Vector3 Vector3::operator*(Vector3 const& rhs) const
{
	Vector3 tmp(*this);
	tmp*=rhs;
	return tmp;
}


Vector3& Vector3::operator/=(Vector3 const& rhs)
{
	this->x/=rhs.x;
	this->y/=rhs.y;
	this->z/=rhs.z;
	return *this;
}

Vector3 Vector3::operator/(Vector3 const& rhs) const
{
	Vector3 tmp(*this);
	tmp/=rhs;
	return tmp;
}

Vector3 Vector3::operator+() const
{
	Vector3 temp(*this);
	return temp;
}

Vector3 Vector3::operator-() const
{
	Vector3 temp(*this);
	temp.x=-temp.x;	
	temp.y=-temp.y;	
	temp.z=-temp.z;
	return temp;
}

float Vector3::operator[](int i) const
{
	if(i==0) return x;
	if(i==1) return y;
	if(i==2) return z;
	return 0;
}

float& Vector3::operator[](int i)
{
	if(i==0) return x;
	if(i==1) return y;
	return z;
}

bool Vector3::operator==(Vector3 const& rhs)
{
	if(	abs((int)(x-rhs.x))<0.01 &&
		abs((int)(y-rhs.y))<0.01 &&
		abs((int)(z-rhs.z))<0.01)
	{
		return true;
	}
	return false;
}

bool Vector3::operator!=(Vector3 const& rhs)
{
	return !(*this==rhs);
}

float Vector3::Magnitude(void)
{
	return sqrtf(x*x+y*y+z*z);
}

float Vector3::sqrMagnitude(void)
{
	return x*x+y*y+z*z;
}

void Vector3::Magnitude(float magnitude)
{
	*this *=  magnitude/Magnitude();
}

void Vector3::Normalise(void)
{
	*this *=  1/Magnitude();
}

void Vector3::Set(float x,float y,float z)
{
	this->x=x;
	this->y=y;
	this->z=z;
}

void Vector3::Set(Vector3 const& vec)
{
	x=vec.x;
	y=vec.y;
	z=vec.z;
}


Vector3 Vector3::Cross(Vector3 const& vec2)
{
	return Vector3::Cross(*this,vec2);
}

Vector3 Vector3::Normalised(Vector3 const& vector)
{
	Vector3 tmp(vector);
	tmp.Normalise();
	return tmp;
}

Vector3 Vector3::MoveToward(Vector3 const& from,Vector3 const& to,float step)
{
	Vector3 dir=to - from;	
	if(dir.Magnitude()>0.01f)  //Far enough
	{
		dir.Magnitude(step);	
		dir+=from;
		return dir;
	}	
	else					   //Very near
	{
		return Vector3(to);
	}
}

Vector3 Vector3::Max(Vector3 const& lhs,Vector3 const& rhs)
{
	Vector3 ret;

	if(lhs.x>rhs.x)
		 ret.x=lhs.x;
	else ret.x=rhs.x;

	if(lhs.y>rhs.y)
		 ret.y=lhs.y;
	else ret.y=rhs.y;

	if(lhs.z>rhs.z)
		 ret.z=lhs.z;
	else ret.z=rhs.z;

	return ret;
}

Vector3 Vector3::Min(Vector3 const& lhs,Vector3 const& rhs)
{
	Vector3 ret;

	if(lhs.x<rhs.x)
		 ret.x=lhs.x;
	else ret.x=rhs.x;

	if(lhs.y<rhs.y)
		 ret.y=lhs.y;
	else ret.y=rhs.y;

	if(lhs.z<rhs.z)
		 ret.z=lhs.z;
	else ret.z=rhs.z;

	return ret;
}

Vector3 Vector3::ClampMagnitude(Vector3 const& vector,float maxLength)
{
	Vector3 ret(vector);
	if(ret.Magnitude()>maxLength)
	{
		ret.Magnitude(maxLength);
	}	
	return ret;
}
									
Vector3 Vector3::Project(Vector3 const& vector, Vector3 const& on)
{
	return on * (Dot(vector,on) / Dot(on,on));
}

float Vector3::Angle(Vector3 const& from,Vector3 const& to)
{
	return acosf(Dot(Normalised(from),Normalised(to)));
	// could calculate axis also: http://www.euclideanspace.com/maths/algebra/vectors/angleBetween/
}
Vector3 Vector3::Reflection(Vector3 const& in,Vector3 const& normal)
{
	return in-(normal*Dot(in,normal)*2);
}
