#pragma once
class CheckPoint
{
private:
	float x;
	float y;
	float z;
public:
	CheckPoint(float x, float y, float z);
	~CheckPoint();
	float getX() const;
	float getY() const;
	float getZ() const;
	void setX(float x);
	void setY(float y);
	void setZ(float z);
};

