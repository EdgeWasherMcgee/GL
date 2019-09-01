#include "common/renderer.h"

class Camera {

public:

	Camera();
	~Camera();

	void lookAt(glm::vec3 pos);

	void move(glm::vec3 mag);

	void setPos(glm::vec3 mag);

	glm::mat4 viewMatrix = glm::mat4(1);

private:

	float FOV;

};