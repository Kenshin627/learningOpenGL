#include <imgui/imgui.h>

#include "TestTexture.h"

namespace test {
    TestTexture::TestTexture(const ImVec2& viewport):viewport(viewport),
        translation(glm::vec3(0.5f, 0.0f, 0.0f)),
        m_Proj(glm::ortho(-1., 1., -1.0, 1.0, -1.0, 1.0)),
        m_View(glm::mat4(1.0f)),
        m_Model(glm::translate(glm::mat4(1.0f), translation))
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
        m_VAO = std::make_unique<VertexArray>();

        //VBO
        m_VBO = std::make_unique<VertexBuffer>(4.0f * 4.0f * sizeof(float), vertexArray);

        //LAYOUT
        VertexBufferLayout layout;
        layout.push<float>(2);
        layout.push<float>(2);
        m_VAO->addBuffer(*m_VBO, layout);

        //IBO
        m_IBO = std::make_unique<IndexBuffer>(6, indices);
        
        //Shader
        m_Shader = std::make_unique<Shader>("resource/shaders/basic/");
        m_Shader->bind();

        //Transform

        //Texture
        m_Texture = std::make_unique<Texture>("resource/textures/container.jpg");
        m_Texture->bind(0);
        m_Shader->SetUniform1i("sampler", 0);

        //Renderer
        m_Renderer = std::make_unique<Renderer>();

        //FBO
        m_FBO = std::make_unique<FrameBuffer>(viewport[0], viewport[1]);
	}

	TestTexture::~TestTexture() {}

	void TestTexture::onUpdate(float deltaTime) {}

	void TestTexture::onRender() 
    {
        m_Renderer->clear();        
        m_Shader->bind();        
        m_Model = glm::translate(glm::mat4(1.0f), translation);
        glm::mat4 mvp = m_Proj * m_View * m_Model;
        m_Shader->setUniformMat4v("u_Mvp", mvp);
        m_FBO->bind();
        //m_Renderer->clear();
        m_Renderer->draw(*m_VAO, *m_IBO, *m_Shader);
    }

    void TestTexture::onImGuiRender()
    {
        ImGui::SliderFloat3("translation", &translation.x, -.5f, 0.5f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f /ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }
}