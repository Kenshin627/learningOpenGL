#include "Camera.h"

Camera::Camera(float verticalFov, float nearPlane, float farPlane, float width, float height, const glm::vec3& pos, const glm::vec3& direction, const glm::vec3& up, float speed):verticalFov(glm::radians(verticalFov)), nearPlane(nearPlane), farPlane(farPlane), viewportWidth(width), viewportHeight(height), m_Position(pos), m_Direction(direction), m_Up(up), speed(speed)
{
	ComputeView();
	CompoteProjection();
}

Camera::~Camera() {}

void Camera::ComputeView()
{
	view = glm::lookAt(m_Position, m_Position + m_Direction, m_Up);
}

void Camera::CompoteProjection()
{
	projection = glm::perspectiveFov(verticalFov, viewportWidth, viewportHeight, nearPlane, farPlane);
}