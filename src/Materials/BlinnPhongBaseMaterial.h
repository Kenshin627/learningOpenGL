#pragma once

#include <string>
#include <glm/glm.hpp>

#include "Shader.h"

class BlinnPhongMaterial
{
public:
	const std::string& name;
	const glm::vec3& ambientColor;
	const glm::vec3& diffuseColor;
	const glm::vec3& specularColor;
	float shininess;
	std::unique_ptr<Shader> shader;	
public:
	BlinnPhongMaterial(const std::string& name, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess);
	~BlinnPhongMaterial();
	void setUniforms() const ;
};