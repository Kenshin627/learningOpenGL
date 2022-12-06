#include "BlinnPhongBaseMaterial.h"

BlinnPhongMaterial::BlinnPhongMaterial(const std::string& name, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess):
	name(name),
	ambientColor(ambient),
	diffuseColor(diffuse),
	specularColor(specular),
	shininess(shininess)
{
	shader = std::make_unique<Shader>("resource/shaders/BlinnPhong/");
}

BlinnPhongMaterial::~BlinnPhongMaterial()
{
	
}

void BlinnPhongMaterial::setUniforms() const
{
	shader->bind();
	shader->setUniform3f("material.ambientColor", ambientColor);
	shader->setUniform3f("material.diffuseColor", diffuseColor);
	shader->setUniform3f("material.specularColor", specularColor);
	shader->SetUniform1f("material.shininess", shininess);
}