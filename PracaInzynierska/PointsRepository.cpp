#include "PointsRepository.h"

std::vector<CheckPoint> PointsRepository::pointsVector;

PointsRepository::PointsRepository()
{
}


PointsRepository::~PointsRepository()
{
}

void PointsRepository::renderAllPoints()
{
}

void PointsRepository::addPoint(CheckPoint point) {
	this->pointsVector.push_back(point);
}

void PointsRepository::removePoint(int point) {
	//this->pointsVector.erase(this->pointsVector.begin() + point);
	this->pointsVector.pop_back();
}

const int PointsRepository::getVerticlesSizeForCube() const {
	return this->VERTICLES_SIZE_FOR_CUBE;
}

const float * PointsRepository::getPointVerticles() const {
	return this->POINT_VERTICLES;
}

std::vector<CheckPoint> PointsRepository::getPointsVector() const {
	return this->pointsVector;
}
