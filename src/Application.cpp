#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

static std::string readShader(std::string shaderPath)
{
    std::ifstream stream(shaderPath);
    std::string line;
    std::stringstream ss;
    while (getline(stream,line))
    {
        ss << line << "\n";
    }
    stream.close();
    return ss.str();
}

static unsigned int compileShader(unsigned int shaderType, const std::string& source)
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
        std::string type = shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment";
        std::cout << type << "Shader compile failed:" << message << "\n";
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader)
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

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(1024, 768, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "[ERROR]: glew init error!\n";
    }

    float vertexArray[12] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f, 0.5f,
        -0.5f, 0.5f,

    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    //VAO
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    

    //VBO
    unsigned int vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), vertexArray, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    //IBO
    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    std::string vertexShader = readShader("resource/shaders/basic/vertex.glsl");
    std::string fragmentShader = readShader("resource/shaders/basic/fragment.glsl");
    unsigned int program = createShader(vertexShader, fragmentShader);
    glUseProgram(program); 

    unsigned int location = glGetUniformLocation(program, "u_Color");
    if (location != -1)
    {
        glUniform4f(location, 0.2, 0.3, 0.8, 1.0);
    }

    //clear
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glUniform4f(location, 0.2, 0.3, 0.8, 1.0);
        glBindVertexArray(vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */ 
        glfwPollEvents();
    }
    glDeleteProgram(program);
    glfwTerminate();
    return 0;
} 