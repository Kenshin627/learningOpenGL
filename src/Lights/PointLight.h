#pragma once

#include <glm/glm.hpp>

class PointLight
{
private:
	glm::vec3 m_Position;
	glm::vec3 m_Color;
public:
	PointLight(const glm::vec3& color, const glm::vec3& position);
	~PointLight();
	inline void setColor(const glm::vec3& color) { m_Color = color; }
	inline void setPosition(const glm::vec3& position) { m_Position = position; }
	inline glm::vec3& getColor() { return m_Color; };
	inline glm::vec3& getPosition() { return m_Position; }
};