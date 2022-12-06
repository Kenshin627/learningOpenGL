#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <glm/glm.hpp>

class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> uniforms;
public:
	Shader(const std::string& filePath);
	~Shader();

	void bind() const;
	void unbind() const;

	void SetUniform4f(const std::string& name, const glm::vec4& v);
	void SetUniform1i(const std::string& name, int v);
	void SetUniform1f(const std::string& name, float v);
	void setUniform3f(const std::string& name, const glm::vec3& v);
	void setUniformMat4v(const std::string& name, const glm::mat4& matrix);
	void setUniformMat3v(const std::string& name, const glm::mat3& matrix);
private:
	int GetUniformLocation(const std::string& name);
	std::string readShader(std::string& shaderPath);
	unsigned int compileShader(unsigned int shaderType, const std::string& source);
	unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
};