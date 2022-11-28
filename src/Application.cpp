#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#include "Renderer.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
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
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui::StyleColorsDark();
    ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
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
        glm::mat4 proj = glm::ortho(-1., 1., -1.0, 1.0, -1.0, 1.0);
        glm::mat4 view = glm::mat4(1.0f);
        glm::fvec3 translation(0.5f, 0.0f, 0.0f);
        
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

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            shader.bind();
            
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
            glm::mat4 mvp = proj * view * model;
            shader.setUniformMat4v("u_Mvp", mvp);
            renderer.draw(vao, ibo, shader);
            {
                ImGui::Begin("OpenGL Renderer");
                ImGui::SliderFloat3("translation", &translation.x, -.5f, 0.5f);
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    return 0;
} 