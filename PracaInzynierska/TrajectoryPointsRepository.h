#pragma once
#pragma once
#include"CheckPoint.h"
#include <vector>
#include "MapData.h"
class TrajectoryPointsRepository
{

private:
	const static int VERTICLES_SIZE = 150;
	const int VERTICLES_SIZE_FOR_CUBE = VERTICLES_SIZE * 4;
	const float POINT_VERTICLES[VERTICLES_SIZE] = {
		0.0f, 0.3f, 0.0f,  0.0f, 0.0f, //1
		-1.0f, 0.0f, 1.0f,  1.0f, 0.0f,//3
		0.0f,  0.0f, 0.0f,  1.0f, 1.0f,//4
		0.0f, -0.3f, 0.0f,  0.0f, 0.0f,//2
		-1.0f, 0.0f, 1.0f,  1.0f, 0.0f,//3
		0.0f,  0.0f, 0.0f,  1.0f, 1.0f,//4

		0.0f, 0.3f,  0.0f,  0.0f, 0.0f,//1
		1.0f, 0.0f,  -1.0f,  1.0f, 0.0f,//5
		-1.0f, 0.0f,  -1.0f,  1.0f, 1.0f,//6
		0.0f, -0.3f,  0.0f,  0.0f, 0.0f,//2
		1.0f, 0.0f,  -1.0f,  1.0f, 0.0f,//5
		-1.0f, 0.0f,  -1.0f,  1.0f, 1.0f,//6

		0.0f,  0.3f,  0.0f,  0.0f, 0.0f,//1
		-1.0f,  0.0f, -1.0f,  1.0f, 0.0f,//6
		-1.0f, 0.0f, 1.0f,  1.0f, 1.0f,//3
		0.0f,  -0.3f,  0.0f,  0.0f, 0.0f,//2
		-1.0f,  0.0f, -1.0f,  1.0f, 0.0f,//6
		-1.0f, 0.0f, 1.0f,  1.0f, 1.0f,//3

		0.0f,  0.3f,  0.0f,  0.0f, 0.0f,//1
		0.0f,  0.0f, 0.0f,  1.0f, 0.0f,//4
		1.0f, 0.0f, -1.0f,  1.0f, 1.0f,//5
		0.0f,  -0.3f,  0.0f,  0.0f, 0.0f,//2
		0.0f,  0.0f, 0.0f,  1.0f, 0.0f,//4
		1.0f, 0.0f, -1.0f,  1.0f, 1.0f//5
	};
	static std::vector<CheckPoint> pointsVector;
public:
	TrajectoryPointsRepository();
	~TrajectoryPointsRepository();
	unsigned int VBO, VAO;
	void renderAllPoints();
	void addPoint(CheckPoint point);
	void removePoint(int point);
	const int getVerticlesSizeForCube() const;
	const float *getPointVerticles() const;
	std::vector<CheckPoint> getPointsVector() const;
};

