#include "Trajectory.h"



Trajectory::Trajectory()
{
	
}


Trajectory::~Trajectory()
{
}

 float  Trajectory::drow(float tmpTime, glm::mat4 model, GLint modelLoc, GLuint textureTrajectory, TrajectoryPointsRepository *pointsRepositoryTrajectory)
{
	if (tmpTime + 1.5 < glfwGetTime()) {
		tmpTime = glfwGetTime();
		CheckPoint point((dronePosition::pos_object_x - Setup::startingPointX) / MapData::scaleX,
			dronePosition::height, (Setup::startingPointY - dronePosition::pos_object_y) / MapData::scaleY);
		pointsRepositoryTrajectory->addPoint(point);
		if (pointsRepositoryTrajectory->getPointsVector().size() > 35)
			pointsRepositoryTrajectory->removePoint(0);
	}
	for (unsigned int i = 0; i < pointsRepositoryTrajectory->getPointsVector().size(); i++) {
		glm::mat4 point;
		glBindTexture(GL_TEXTURE_2D, textureTrajectory);
		point = glm::translate(point, glm::vec3(pointsRepositoryTrajectory->getPointsVector().at(i).getX(),
			pointsRepositoryTrajectory->getPointsVector().at(i).getY()+ 0.07,
			pointsRepositoryTrajectory->getPointsVector().at(i).getZ()));
		point = glm::scale(point, glm::vec3(0.004f, 0.004f, 0.004f));
		point = glm::rotate(point, dronePosition::direction, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(point));
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	return tmpTime;
}
 
