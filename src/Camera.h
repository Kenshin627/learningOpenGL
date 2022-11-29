#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
private:
	float verticalFov;
	float nearPlane;
	float farPlane;
	float viewportWidth;
	float viewportHeight;
	glm::vec3 m_Position;
	glm::vec3 m_Direction;
	glm::vec3 m_Up;
	float speed;
	glm::mat4 view;
	glm::mat4 projection;
public:
	Camera(float verticalFov, float nearPlane, float farPlane, float viewportWidth, float viewportHeight, const glm::vec3& pos, const glm::vec3& direction, const glm::vec3& up, float speed);
	~Camera();
public:
	void ComputeView();
	void CompoteProjection();
	inline const glm::mat4& GetView() const { return view; };
	inline const glm::mat4& GetProjection() const { return projection; };
};