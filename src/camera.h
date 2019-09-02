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

	float FOV;

	glm::mat4 viewMatrix = glm::mat4(1);
	glm::mat4 perspectiveMatrix = glm::perspective(FOV, (float)16/(float)10, 0.1f, 100.0f);

private:

	// glm::vec3 xRot = glm::vec3(0, 1, 0);
};