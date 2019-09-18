#pragma once
#include "common/renderer.h"

class Camera {

public:

	Camera();
	~Camera();

	void lookAt(glm::vec3 pos);

	void move(glm::vec3 mag);

	void setPos(glm::vec3 mag);

	void rotateY(float angle);

	void rotateZ(float angle);

	void rotateAround(glm::vec3 vec);

	glm::mat4 getViewMatrix() const;
	glm::mat4 getPerspectiveMatrix() const;

	float FOV;


private:

	glm::vec3 m_Front;
	glm::vec3 m_Side;
	glm::vec3 m_Up;

	glm::vec3 m_Pos;

	glm::mat4 m_PerspectiveMatrix = glm::perspective(FOV, (float)16/(float)10, 0.1f, 100.0f);


};