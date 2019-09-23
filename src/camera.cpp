#include "camera.h"

Camera::Camera() {

	FOV = 90.0f;
	m_PerspectiveMatrix = glm::transpose(glm::perspective(FOV, (float)16/(float)10, 0.1f, 100.0f));
	// m_PerspectiveMatrix = glm::mat4(1);

	m_Front = glm::vec3(1.0f, 0.0f, 0.0f);
	m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_Side = glm::vec3(0.0f, 0.0f, 1.0f);

	m_Pos = glm::vec3(0.0f, 0.0f, 0.0f);

}

Camera::~Camera() {

}


void Camera::lookAt(glm::vec3 pos) {

	glm::vec3 normPos = glm::normalize(pos);

	m_Front = normPos;

	if (!(glm::abs(normPos.z) > 0.98f)) {

		m_Side = glm::normalize(glm::cross(m_Front, glm::vec3(0.0f, 1.0f, 0.0f)));

	}

	m_Up = glm::cross(m_Front, m_Side);

}

void Camera::move(glm::vec3 mag) {

	m_Pos += mag;

}

void Camera::setPos(glm::vec3 mag) {

	m_Pos = mag;

}

void Camera::rotateY(float angle) {

	// Makes the correct rotations in worldSpace
	glm::vec3 baseRotationMatrixFront = glm::vec3( glm::cos(angle), glm::sin(angle), 1);
	glm::vec3 baseRotationMatrixUp	  = glm::vec3(-glm::sin(angle), glm::cos(angle), 1);

	m_Front = m_Front * baseRotationMatrixFront;
	m_Up 	= m_Up	  * baseRotationMatrixUp;

}
	
void Camera::rotateZ(float angle) {

	// Makes the correct rotations in worldSpace
	glm::vec3 baseRotationMatrixFront = glm::vec3( glm::cos(angle), 1, glm::sin(angle));
	glm::vec3 baseRotationMatrixSide  = glm::vec3(-glm::sin(angle), 1, glm::cos(angle));

	m_Front = m_Front * baseRotationMatrixFront;
	m_Side  = m_Side  * baseRotationMatrixSide;

}

glm::mat4 Camera::getViewMatrix() const {

	//Assembles the ViewMatrix from the existing parameters
	return glm::mat4(

		m_Front.x, m_Up.x, m_Side.x,  m_Pos.x,
		m_Front.y, m_Up.y, m_Side.y,  m_Pos.y,
		m_Front.z, m_Up.z, m_Side.z,  m_Pos.z,
		0.0f, 	   0.0f,   0.0f, 	  1.0f
		);

}

glm::mat4 Camera::getPerspectiveMatrix() const {

	//This function is only here for consistancy, I could've made it public
	return m_PerspectiveMatrix;

}