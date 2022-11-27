#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

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

        ////clear
        vbo.unbind();
        ibo.unbind();
        vao.unbind();
        shader.unbind();

        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT);

            shader.bind();
            shader.SetUniform4f("u_Color", 0.2, 0.3, 0.8, 1.0);
            vao.bind();
            ibo.bind();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();
    }
    return 0;
} 