#pragma once
#include<iostream>
#include<glm/glm/glm.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include<string>

class Camera {
public:
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Position;
	float yaw = -90.0f;
	float pitch = 0.0f;
	enum cameraMove{FORWARD,BACK,RIGHT,LEFT};

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f)) {
		Position = position;
		Front = front;
		Up = up;
	};
	glm::mat4 getViewMatrix() {
		return glm::lookAt(Position,Position+Front, Up);
	}
	void processKeyMovement(std::string type,float delta) {
		float vel = 1.5f * delta;
		if (type == "FORWARD") {
			Position += vel * glm::normalize(Front);
		}
		else if (type == "BACK") {
			Position -= vel * glm::normalize(Front);
		}
		else if (type == "RIGHT") {
			Position += vel * glm::normalize(glm::cross(Front, Up));
		}
		else if (type == "LEFT") {
			Position -= vel * glm::normalize(glm::cross(Front, Up));
		}
	}
	void processMouseMovement(float* xoffset, float* yoffset) {
		*xoffset *= 0.1;
		*yoffset *= 0.1;

		yaw += *xoffset;
		pitch += *yoffset;

		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		Front = glm::normalize(front);
	}
};