#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

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

	void SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4);
private:
	unsigned int GetUniformLocation(const std::string& name);
	std::string readShader(std::string& shaderPath);
	unsigned int compileShader(unsigned int shaderType, const std::string& source);
	unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
};