#include "Camera.h"
#include <iostream>

Camera::Camera(sf::RenderWindow &window) : window(window) {
	yaw		= 0.0f;
	pitch	= 0.0f;
	msec	= 0.0f;

	test	= 0.0f;
}

Camera::Camera(sf::RenderWindow &window, float pitch ,float yaw ,glm::vec3 position) : window(window) {
	this->pitch		= pitch;
	this->yaw		= yaw;
	this->position	= position; 
	this->msec		= 0.0f;

	test	= 0.0f;
}

void Camera::updateCamera(float msec) {
	this->msec = msec * 0.01f;

	// TODO YAW AND PITCH
	//pitch -= sf::Mouse::getPosition().y;
	//yaw -= sf::Mouse::getPosition().x;

	//pitch = std::min(pitch , 90.0f);
	//pitch = std::max(pitch , -90.0f);

	//if(yaw < 0) {
	//	yaw += 360.0f;
	//}
	//if(yaw > 360.0f) {
	//	yaw -= 360.0f;
	//}
}

glm::mat4 Camera::buildViewMatrix() {
	// ADD THE 2 ROTATIONS IN AFTER THEY ARE FIXED
	//return	glm::rotate(glm::mat4(), -pitch ,glm::vec3 (1 ,0 ,0)) *
	//		glm::rotate(glm::mat4(), -yaw ,glm::vec3 (0 ,1 ,0)) *
	//		glm::translate(glm::mat4(), -position);

	return glm::translate(glm::mat4(), glm::vec3(-position));
}

void Camera::keyW() {
	glm::vec4 p = glm::rotate(glm::mat4(), yaw , glm::vec3 (0.0f ,1.0f ,0.0f)) * glm::vec4 (0.0f ,0.0f , -1.0f, 1.0f) * msec;
	position += glm::vec3(p.x, p.y, p.z);
}

void Camera::keyA() {
	glm::vec4 p = glm::rotate(glm::mat4(), yaw , glm::vec3 (0.0f ,1.0f ,0.0f)) * glm::vec4 ( -0.2f ,0.0f ,0.0f, 1.0f) * msec ;
	position += glm::vec3(p.x, p.y, p.z);
}

void Camera::keyS() {
	glm::vec4 p = glm::rotate(glm::mat4(), yaw , glm::vec3 (0.0f ,1.0f ,0.0f)) * glm::vec4 (0.0f ,0.0f , -1.0f, 1.0f) * msec;
	position -= glm::vec3(p.x, p.y, p.z);
}

void Camera::keyD() {
	glm::vec4 p = glm::rotate(glm::mat4(), yaw , glm::vec3 (0.0f ,1.0f ,0.0f)) * glm::vec4 ( -0.2f ,0.0f ,0.0f, 1.0f) * msec ;
	position -= glm::vec3(p.x, p.y, p.z);
}

void Camera::keyShift() {
	position.y += msec;
}

void Camera::keySpace() {
	position.y -= msec;
}

void Camera::mouseLeft() {
	// TODO
	//std::cout << "MOUSE" << std::endl;
	//test -= sf::Mouse::getPosition().y;
	//if(test < 0) {
	//	test += 360.0f;
	//}
	//if(test > 360.0f) {
	//	test -= 360.0f;
	//}
}