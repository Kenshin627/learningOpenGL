#include "Shader.h"
#include <GL/glew.h>

Shader::Shader(const std::string& filePath):m_FilePath(filePath),m_RendererID(0)
{
    std::string vertexPath = filePath + "vertex.glsl";
    std::string vertexShader = readShader(vertexPath);

    std::string fragmentPath = filePath + "fragment.glsl";
    std::string fragmentShader = readShader(fragmentPath);

    m_RendererID = createShader(vertexShader, fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

void Shader::bind() const
{
    glUseProgram(m_RendererID);
}

void Shader::unbind() const
{
    glUseProgram(0);
}

void Shader::SetUniform4f(const std::string& name, const glm::vec4& v)
{
    glUniform4f(GetUniformLocation(name), v.x, v.y, v.z, v.w);
}

void Shader::SetUniform1i(const std::string& name, int v)
{
    glUniform1i(GetUniformLocation(name), v);
}

void Shader::SetUniform1f(const std::string& name, float v)
{
    glUniform1f(GetUniformLocation(name), v);
}

void Shader::setUniform3f(const std::string& name, const glm::vec3& v)
{
    glUniform3f(GetUniformLocation(name), v.x, v.y, v.z);
}

void Shader::setUniformMat4v(const std::string& name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::setUniformMat3v(const std::string& name, const glm::mat3& matrix)
{
    glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (uniforms.find(name) != uniforms.end())
    {
        return uniforms[name];
    }
    int location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1)
    {
        std::cout << "can't find uniform" << name << "location\n";
    }
    uniforms[name] = location;
    return location;
}

std::string Shader::readShader(std::string& shaderPath)
{
    std::ifstream stream(shaderPath);
    std::string line;
    std::stringstream ss;
    while (getline(stream, line))
    {
        ss << line << "\n";
    }
    stream.close();
    return ss.str();
}

unsigned int Shader::compileShader(unsigned int shaderType, const std::string& source)
{
    unsigned int shader = glCreateShader(shaderType);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int shader_compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_compiled);
    if (shader_compiled == GL_FALSE)
    {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)_malloca(length * sizeof(char));
        glGetShaderInfoLog(shader, length, &length, message);

        std::cout 
            << 
            (shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment")
            << 
            "Shader compile failed:" 
            << 
            message 
            << "\n";
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

