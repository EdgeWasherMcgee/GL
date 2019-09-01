#include "camera.h"

void Camera::lookAt(glm::vec3 pos) {

	glm::vec3 relative = pos - glm::vec3(viewMatrix[3][0], viewMatrix[3][1], viewMatrix[3][2]);
	glm::vec3 xDir = relative/glm::length(relative);
	viewMatrix[0][0] = xDir[0];
	viewMatrix[1][0] = xDir[1];
	viewMatrix[2][0] = xDir[2];

}

void Camera::move(glm::vec3 mag) {

	viewMatrix[3][0] += mag[0];
	viewMatrix[3][1] += mag[0];
	viewMatrix[3][2] += mag[0];

}

void Camera::setPos(glm::vec3 mag) {

	viewMatrix[3][0] = mag[0];
	viewMatrix[3][1] = mag[0];
	viewMatrix[3][2] = mag[0];

}