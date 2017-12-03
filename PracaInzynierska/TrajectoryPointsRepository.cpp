

#include "TrajectoryPointsRepository.h"

std::vector<CheckPoint> TrajectoryPointsRepository::pointsVector;

TrajectoryPointsRepository::TrajectoryPointsRepository()
{
}


TrajectoryPointsRepository::~TrajectoryPointsRepository()
{
}

void TrajectoryPointsRepository::renderAllPoints()
{
}

void TrajectoryPointsRepository::addPoint(CheckPoint point) {
	this->pointsVector.push_back(point);
}

void TrajectoryPointsRepository::removePoint(int point) {
	this->pointsVector.erase(this->pointsVector.begin() + point);
	//this->pointsVector.pop_back();
}

const int TrajectoryPointsRepository::getVerticlesSizeForCube() const {
	return this->VERTICLES_SIZE_FOR_CUBE;
}

const float * TrajectoryPointsRepository::getPointVerticles() const {
	return this->POINT_VERTICLES;
}

std::vector<CheckPoint> TrajectoryPointsRepository::getPointsVector() const {
	return this->pointsVector;
}
