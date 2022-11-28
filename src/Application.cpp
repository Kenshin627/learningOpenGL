#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#include "Renderer.h"

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

    {
        //Data
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
        VertexArray vao;

        //VBO
        VertexBuffer vbo(4 * 2 * sizeof(float), vertexArray);

        //LAYOUT
        VertexBufferLayout layout;
        layout.push<float>(2);
        vao.addBuffer(vbo, layout);

        //IBO
        IndexBuffer ibo(6, indices);

        //Shader
        Shader shader("resource/shaders/basic/");
        shader.bind();
        shader.SetUniform4f("u_Color", 0.2, 0.3, 0.8, 1.0);

        //clear
        vbo.unbind();
        ibo.unbind();
        vao.unbind();
        shader.unbind();

        //Renderer
        Renderer renderer;

        while (!glfwWindowShouldClose(window))
        {
            renderer.clear();
            shader.bind();
            shader.SetUniform4f("u_Color", 0.2, 0.3, 0.8, 1.0);
            renderer.draw(vao, ibo, shader);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();
    }
    return 0;
} 