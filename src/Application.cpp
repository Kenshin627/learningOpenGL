#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#include "Renderer.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
        float vertexArray[20] = {
            -0.5f, -0.5f, 0.0f, 0.0f,
             0.5f, -0.5f, 1.0f, 0.0f,
             0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 1.0f

        };
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        //VAO
        VertexArray vao;

        //VBO
        VertexBuffer vbo(4 * 4 * sizeof(float), vertexArray);

        //LAYOUT
        VertexBufferLayout layout;  
        layout.push<float>(2);
        layout.push<float>(2);
        vao.addBuffer(vbo, layout);

        //IBO
        IndexBuffer ibo(6, indices);

        //Shader
        Shader shader("resource/shaders/basic/");
        shader.bind();

        //Transform
        glm::mat4 proj = glm::ortho(-5.0, 5.0, -1.0, 1.0, -1.0, 1.0);
        shader.setUniformMat4v("u_Projection", proj);

        //Texture
        Texture texture("resource/textures/container.jpg");
        texture.bind(0);
        shader.SetUniform1i("sampler", 0);

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
            renderer.draw(vao, ibo, shader);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();
    }
    return 0;
} 