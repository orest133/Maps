#include "CheckPoint.h"

CheckPoint::CheckPoint(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}


CheckPoint::~CheckPoint()
{
}

float CheckPoint::getX() const
{
	return this->x;
}

float CheckPoint::getY() const
{
	return this->y;
}

float CheckPoint::getZ() const
{
	return this->z;
}

void CheckPoint::setX(float x)
{
	this->x = x;
}

void CheckPoint::setY(float y)
{
	this->y = y;
}

void CheckPoint::setZ(float z)
{
	this->z = z;
}
