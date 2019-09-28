#include "camera.h"

Camera::Camera() {

	FOV = 70.0f;
	m_PerspectiveMatrix = glm::perspective(FOV, (float)5/(float)3, 0.1f, 100.0f);

	// m_PerspectiveMatrix = glm::mat4(1);

	m_Front = glm::vec3(1.0f, 0.0f, 0.0f);
	m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_Side = glm::vec3(0.0f, 0.0f, 1.0f);

	m_Pos = glm::vec3(0.0f, 0.0f, 0.0f);

}

Camera::~Camera() {

}


void Camera::lookAt(glm::vec3 pos) {

	m_Front = glm::normalize(pos - m_Pos);

	if (!(glm::abs(m_Front.y) > 0.99f))
		m_Side = glm::normalize(glm::cross(m_Front, glm::vec3(0.0f, -1.0f, 0.0f)));
	else
		m_Side = glm::normalize(glm::cross(m_Front, glm::vec3(1.0f, 0.0f, 0.0f)));

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

}
	
void Camera::rotateZ(float angle) {

	// Makes the correct rotations in worldSpace

}

glm::mat4 Camera::getViewMatrix() const {

	//Assembles the ViewMatrix from the existing parameters
	return glm::mat4(

		 m_Front.x, m_Front.y, m_Front.z, 0.0f,
		 m_Up.x,    m_Up.y,    m_Up.z,	  0.0f,
		 m_Side.x,  m_Side.y,  m_Side.z,  0.0f,
		-m_Pos.x,  -m_Pos.y,  -m_Pos.z,   1.0f
		);

}

glm::mat4 Camera::getPerspectiveMatrix() const {

	//This function is only here for consistancy, I could've made it public
	return m_PerspectiveMatrix;

}