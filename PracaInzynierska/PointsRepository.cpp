#include "PointsRepository.h"

std::vector<CheckPoint> PointsRepository::pointsVector;
int PointsRepository::pointer = 0;
bool PointsRepository::editingMode = false;

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
	this->pointsVector.erase(this->pointsVector.begin() + point);
}

const int PointsRepository::getVerticlesSizeForCube() const {
	return this->VERTICLES_SIZE_FOR_CUBE;
}

const float * PointsRepository::getPointVerticles() const {
	return this->POINT_VERTICLES;
}

std::vector<CheckPoint>& PointsRepository::getPointsVector() {
	return this->pointsVector;
}

int PointsRepository::getPointer() const {
	return this->pointer;
}

void PointsRepository::setPointer(int index) {
	if (index >= 0 && index <= VERTICLES_SIZE && index < this->pointsVector.size()) {
		this->pointer = index;
	}
}

bool& PointsRepository::getEditingMode() {
	return this->editingMode;
}

void PointsRepository::setEditingMode(bool editingMode) {
	this->editingMode = editingMode;
}
