#include "..\pch.h"
#include "Quaternion.h"

using namespace SBM;

Quaternion::Quaternion(void)
{
	x=0;
	y=0;
	z=0;
	w=1;
}

Quaternion::Quaternion(float x,float y,float z,float w)
{
	this->x=x;
	this->y=y;
	this->z=z;
	this->w=w;
}

Quaternion::~Quaternion(void)
{
}

Quaternion& Quaternion::operator+=(Quaternion const& rhs)
{
	this->x+=rhs.x;
	this->y+=rhs.y;
	this->z+=rhs.z;
	this->w+=rhs.w;
	return *this;
}

Quaternion Quaternion::operator+(Quaternion const& rhs) const
{
	Quaternion tmp(*this);
	tmp+=rhs;
	return tmp;
}

Quaternion& Quaternion::operator-=(Quaternion const& rhs)
{
	this->x-=rhs.x;
	this->y-=rhs.y;
	this->z-=rhs.z;
	this->w-=rhs.w;
	return *this;
}

Quaternion Quaternion::operator-(Quaternion const& rhs) const
{
	Quaternion tmp(*this);
	tmp-=rhs;
	return tmp;
}

Quaternion& Quaternion::operator*=(Quaternion const& rhs)
{
	Quaternion ret;
	ret.x = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
	ret.y = w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x;
	ret.z = w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w;
	ret.w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;

	x=ret.x;
	y=ret.y;
	z=ret.z;
	w=ret.w;
	return *this;
}

Quaternion Quaternion::operator*(Quaternion const& rhs) const
{
	Quaternion tmp(*this);
	tmp*=rhs;
	return tmp;
}

Vector3 Quaternion::operator*(Vector3 const& rhs) const
{
	return Matrix() *rhs;
}

Quaternion Quaternion::operator+()
{
	Quaternion temp(*this);
	return temp;
}

Quaternion Quaternion::operator-()
{
	Quaternion temp(*this);
	temp.Inverse();
	return temp;
}

float Quaternion::operator[](int i) const
{
	if(i==0) return x;
	if(i==1) return y;
	if(i==2) return z;
	if(i==3) return w;
	return 0;
}

float& Quaternion::operator[](int i)
{
	if(i==0) return x;
	if(i==1) return y;
	if(i==2) return z;
	return w;
}

bool Quaternion::operator==(Quaternion const& rhs)
{
	if(	abs((int)(x-rhs.x))<0.01 &&
		abs((int)(y-rhs.y))<0.01 &&
		abs((int)(z-rhs.z))<0.01 &&
		abs((int)(w-rhs.w))<0.01)
	{
		return true;
	}
	return false;
}

bool Quaternion::operator!=(Quaternion const& rhs)
{
	return !(*this==rhs);
}

float Quaternion::Magnitude()
{
	return sqrtf(x*x+y*y+z*z+w*w);
}

void Quaternion::Inverse()
{
	x=-x;
	y=-y;
	z=-z;
	w=-w;
}

void  Quaternion::Normalise()
{
	float mag= Magnitude();
	x=x/mag;
	y=y/mag;
	z=z/mag;
	w=w/mag;
}

Matrix4 Quaternion::Matrix() const
{
	Matrix4 ret;
	float xx      = x * x;
    float xy      = x * y;
    float xz      = x * z;
    float xw      = x * w;

    float yy      = y * y;
    float yz      = y * z;
    float yw      = y * w;

    float zz      = z * z;
    float zw      = z * w;

	ret.m[0] = 1 - 2 * ( yy + zz );
	ret.m[1] =     2 * ( xy - zw );
	ret.m[2] =     2 * ( xz + yw );
	//ret.m[3] = 0;

	ret.m[4] =     2 * ( xy + zw );
	ret.m[5] = 1 - 2 * ( xx + zz );
	ret.m[6] =     2 * ( yz - xw );
	//ret.m[7] = 0;

	ret.m[8]  =     2 * ( xz - yw );
	ret.m[9]  =     2 * ( yz + xw );
	ret.m[10] = 1 - 2 * ( xx + yy );
	//ret.m[11] = 0;

	//ret.m[12]=0;
	//ret.m[13]=0;
	//ret.m[14]=0;
	ret.m[15]=1;
	return ret;
}

Vector3 Quaternion::ToEuler()
{
	Vector3 tmp;
	float sqw=w*w;
	float sqx=x*x;
	float sqy=y*y;
	float sqz=z*z;

	float unit=sqx+sqy+sqz+sqw;
	float test=x*y+z*w;

	if(test>0.499*unit)
	{
		tmp.x = 2*atan2f(x,w);
		tmp.y = (float)M_PI/2;
		tmp.z = 0;
		return tmp;
	}

	if(test <-0.499*unit)
	{
		tmp.x =- (2*atan2f(x,w));
		tmp.y =-(float)M_PI/2;
		tmp.z =0;
		return tmp;
	}

	
	tmp.x = (float)atan((2*y*w-2*x*z) / (sqx-sqy-sqz+sqw));
	tmp.y = (float)asin(2*test/unit);
	tmp.z = (float)atan((2*x*w-2*y*z) / (-sqx+sqy-sqz+sqw));

	/*tmp.x =atan2(2*x*w-2*x*z,sqx-sqy-sqz-sqw);
	tmp.y =asin(2*test/unit);
	tmp.z =atan2(2*x*w-2*y*z,-sqx+sqy-sqz+sqw);*/
	return tmp;
}

AxisAngle Quaternion::ToAxisAngle()
{
	SBM::AxisAngle tmp;

	Quaternion tempThis=Normalised(*this);

	tmp.angle=2*acosf(tempThis.w);

	float s= sqrtf(1-tempThis.w*tempThis.w);
	if(s<0.001)
	{
		tmp.axis.x=tempThis.x;
		tmp.axis.y=tempThis.y;
		tmp.axis.z=tempThis.z;
	}
	else
	{
		tmp.axis.x=tempThis.x/s;
		tmp.axis.y=tempThis.y/s;
		tmp.axis.z=tempThis.z/s;
	}

	return tmp;
}

Quaternion Quaternion::Normalised(Quaternion const& quaternion)
{
	Quaternion temp(quaternion);
	temp.Normalise();
	return temp;
}

Quaternion Quaternion::Inversed(Quaternion const& quaternion)
{
	Quaternion temp(quaternion);
	temp.Inverse();
	return temp;
}

Quaternion Quaternion::Euler(float x,float y,float z)
{
	float c1=cosf(y/2);
	float s1=sinf(y/2);

	float c2=cosf(z/2);
	float s2=sinf(z/2);

	float c3=cosf(x/2);
	float s3=sinf(x/2);

	float c1c2=c1*c2;
	float s1s2=s1*s2;

	Quaternion ret;
	ret.x=c1c2*s3   +  s1s2*c3;
	ret.y=s1*c2*c3  +  c1*s2*s3;
	ret.z=c1*s2*c3  -  s1*c2*s3;
	ret.w=c1c2*c3   -  s1s2*s3;
	return ret;
}

Quaternion Quaternion::AxisAngle(float x,float y,float z, float angle)
{
	float sin_a=sinf(angle/2);
	float cos_a=cosf(angle/2);

	Quaternion ret;
	ret.x=x*sin_a;
	ret.y=y*sin_a;
	ret.z=z*sin_a;
	ret.w=cos_a;
	ret.Normalise();
	return ret;
}