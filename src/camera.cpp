#include "camera.h"

Camera::Camera() {

	FOV = 180.0f;
	viewMatrix  = glm::mat4(1);
	perspectiveMatrix = glm::perspective(FOV, (float)16/(float)10, 0.1f, 100.0f);

}

Camera::~Camera() {

}

void Camera::lookAt(glm::vec3 pos) {

	glm::vec3 relative = pos - glm::vec3(viewMatrix[3][0], viewMatrix[3][1], viewMatrix[3][2]);
	glm::vec3 xDir = relative/glm::length(relative);
	glm::vec3 zDir;
	glm::vec3 yDir;
	if (!(glm::abs(xDir[1]) > 0.99f)){

		zDir = glm::cross(xDir, glm::vec3(0, 1, 0));
	} else {

		zDir = glm::cross(xDir, glm::vec3(-1, 0, 0));
	}

	yDir = glm::cross(xDir, zDir);

	viewMatrix[0][0] = xDir[0];
	viewMatrix[1][0] = xDir[1];
	viewMatrix[2][0] = xDir[2];

	viewMatrix[0][1] = yDir[0];
	viewMatrix[1][1] = yDir[1];
	viewMatrix[2][1] = yDir[2];

	viewMatrix[0][2] = zDir[0];
	viewMatrix[1][2] = zDir[1];
	viewMatrix[2][2] = zDir[2];

}

void Camera::rotateY(float angle) {

	glm::vec3 newX = glm::cos(angle) * glm::vec3(
		viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]) + glm::sin(angle) * glm::vec3(
		viewMatrix[0][2], viewMatrix[1][2], viewMatrix[2][2]);

	glm::vec3 newZ = -glm::sin(angle) * glm::vec3(
		viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]) + glm::cos(angle) * glm::vec3(
		viewMatrix[0][2], viewMatrix[1][2], viewMatrix[2][2]);

	viewMatrix[0][0] = newX[0];
	viewMatrix[1][0] = newX[1];
	viewMatrix[2][0] = newX[2];

	viewMatrix[0][2] = newZ[0];
	viewMatrix[1][2] = newZ[1];
	viewMatrix[2][2] = newZ[2];

}

void Camera::rotateZ(float angle) {

	glm::vec3 newX = glm::cos(angle) * glm::vec3(
		viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]) + glm::sin(angle) * glm::vec3(
		viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1]);

	glm::vec3 newY = -glm::sin(angle) * glm::vec3(
		viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]) + glm::cos(angle) * glm::vec3(
		viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1]);

	viewMatrix[0][0] = newX[0];
	viewMatrix[1][0] = newX[1];
	viewMatrix[2][0] = newX[2];

	viewMatrix[0][1] = newY[0];
	viewMatrix[1][1] = newY[1];
	viewMatrix[2][1] = newY[2];

}

void Camera::move(glm::vec3 mag) {

	viewMatrix[3][0] += mag[0];
	viewMatrix[3][1] += mag[1];
	viewMatrix[3][2] += mag[2];

}

void Camera::setPos(glm::vec3 mag) {

	viewMatrix[3][0] = mag[0];
	viewMatrix[3][1] = mag[1];
	viewMatrix[3][2] = mag[2];

}