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

	viewMatrix = glm::lookAt(m_Pos, pos, glm::vec3(0.0f, 1.0f, 0.0f));

	m_Front = glm::normalize(pos - m_Pos);

	m_Side = glm::normalize(glm::cross(m_Front, glm::vec3(0.0f, 1.0f, 0.0f)));

	m_Up = glm::cross(m_Side, m_Front);

}

void Camera::move(glm::vec3 mag) {

	m_Pos += mag;

}

void Camera::setPos(glm::vec3 mag) {

	m_Pos = mag;

}

void Camera::rotateY(float angle) {

	// Makes the correct rotations in worldSpace

	glm::mat3 rotationMatrix = glm::mat3(

		 cos(angle), 0.0f, sin(angle),
		 0.0f,		 1.0f, 0.0f,
		-sin(angle), 0.0f, cos(angle)

	);

	m_Front = rotationMatrix * m_Front;
	m_Side = rotationMatrix * m_Side;
	m_Up = rotationMatrix * m_Up;

}
	
void Camera::rotateX(float angle) {

	// Makes the correct rotations in worldSpace

	glm::mat3 rotationMatrix = glm::mat3(

		1.0f, 0.0f, 	   0.0f,
		0.0f, cos(angle), -sin(angle),
		0.0f, sin(angle),  cos(angle)

	);

	m_Front = rotationMatrix * m_Front;
	m_Side = rotationMatrix * m_Side;
	m_Up = rotationMatrix * m_Up;

}

glm::mat4 Camera::getViewMatrix() const {

	//Assembles the ViewMatrix from the existing parameters
	return glm::mat4(

		 m_Side.x,  				m_Up.x,  				-m_Front.x,  			   0.0f,
		 m_Side.y,    				m_Up.y,    				-m_Front.y,	  			   0.0f,
		 m_Side.z, 			   		m_Up.z, 			    -m_Front.z, 			   0.0f,
		-glm::dot(m_Side, m_Pos),  -glm::dot(m_Up, m_Pos),   glm::dot(m_Front, m_Pos), 1.0f
		);
	// return viewMatrix;

}

glm::mat4 Camera::getPerspectiveMatrix() const {

	//This function is only here for consistancy, I could've made it public
	return m_PerspectiveMatrix;

}

glm::vec3 Camera::getFront() const {

	return m_Front;

}

glm::vec3 Camera::getSide() const {

	return m_Side;

}

glm::vec3 Camera::getUp() const {

	return m_Up;

}

glm::vec3 Camera::getPos() const {

	return m_Pos;

}