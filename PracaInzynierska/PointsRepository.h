#pragma once
#include"CheckPoint.h"
#include <vector>
#include "MapData.h"
class PointsRepository
{
private:
	const static int VERTICLES_SIZE = 150;
	const int VERTICLES_SIZE_FOR_CUBE = VERTICLES_SIZE * 4;
	const float POINT_VERTICLES[VERTICLES_SIZE] = {
		0.0f, 0.7f, 0.0f,  0.0f, 0.0f,
		-0.3f, 0.0f, 0.3f,  1.0f, 0.0f,
		0.3f,  0.0f, 0.3f,  1.0f, 1.0f,
		0.0f, -0.7f, 0.0f,  0.0f, 0.0f,
		-0.3f, 0.0f, 0.3f,  1.0f, 0.0f,
		0.3f,  0.0f, 0.3f,  1.0f, 1.0f,

		0.0f, 0.7f,  0.0f,  0.0f, 0.0f,
		0.3f, 0.0f,  -0.3f,  1.0f, 0.0f,
		-0.3f, 0.0f,  -0.3f,  1.0f, 1.0f,
		0.0f, -0.7f,  0.0f,  0.0f, 0.0f,
		0.3f, 0.0f,  -0.3f,  1.0f, 0.0f,
		-0.3f, 0.0f,  -0.3f,  1.0f, 1.0f,

		0.0f,  0.7f,  0.0f,  0.0f, 0.0f,
		-0.3f,  0.0f, -0.3f,  1.0f, 0.0f,
		-0.3f, 0.0f, 0.3f,  1.0f, 1.0f,
		0.0f,  -0.7f,  0.0f,  0.0f, 0.0f,
		-0.3f,  0.0f, -0.3f,  1.0f, 0.0f,
		-0.3f, 0.0f, 0.3f,  1.0f, 1.0f,

		0.0f,  0.7f,  0.0f,  0.0f, 0.0f,
		0.3f,  0.0f, 0.3f,  1.0f, 0.0f,
		0.3f, 0.0f, -0.3f,  1.0f, 1.0f,
		0.0f,  -0.7f,  0.0f,  0.0f, 0.0f,
		0.3f,  0.0f, 0.3f,  1.0f, 0.0f,
		0.3f, 0.0f, -0.3f,  1.0f, 1.0f
	};
	static std::vector<CheckPoint> pointsVector;
public:
	PointsRepository();
	~PointsRepository();
	unsigned int VBO, VAO;
	void renderAllPoints();
	void addPoint(CheckPoint point);
	const int getVerticlesSizeForCube() const;
	const float *getPointVerticles() const;
	std::vector<CheckPoint> getPointsVector() const;
};