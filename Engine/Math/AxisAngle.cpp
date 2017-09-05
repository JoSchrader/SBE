#include "..\pch.h"
#include "AxisAngle.h"

using namespace SBM;

AxisAngle::AxisAngle()
{
	axis= Vector3(0,0,0);
	angle=0;
}
AxisAngle::AxisAngle(Vector3 const& axiss,float angle)
{
	this->axis=axis;
	this->angle=angle;
}
AxisAngle::AxisAngle(float x,float y,float z,float angle)
{
	axis=Vector3(x,y,z);
	this->angle=angle;
}
AxisAngle::~AxisAngle()
{

}