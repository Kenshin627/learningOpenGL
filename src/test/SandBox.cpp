#include <imgui/imgui.h>

#include "SandBox.h"

namespace test {
    SandBox::SandBox(const Camera& camera) :m_Viewport({ 0, 0 }), camera(camera),
        translation(glm::vec3(0.5f, 0.0f, 0.0f)),
        m_Model(glm::translate(glm::mat4(1.0f), translation))
	{
        //Data
        float vertexArray[180] = {
              -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
               0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
               0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
               0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
              -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
              -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

              -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
               0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
               0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
               0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
              -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
              -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
              
              -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
              -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
              -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
              -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
              -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
              -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

               0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
               0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
               0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
               0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
               0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
               0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

              -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
               0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
               0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
               0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
              -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
              -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
              
              -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
               0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
               0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
               0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
              -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
              -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };
        unsigned int indices[] = {
            0, 2, 1,
            0, 3, 2
        };

        //VAO
        m_VAO = std::make_unique<VertexArray>();

        //VBO
        m_VBO = std::make_unique<VertexBuffer>(36.0f, 36.0f * 5.0f * sizeof(float), vertexArray);

        //LAYOUT
        VertexBufferLayout layout;
        layout.push<float>(3);
        layout.push<float>(2);
        m_VAO->addBuffer(*m_VBO, layout);

        //IBO
        //m_IBO = std::make_unique<IndexBuffer>(36, indices);
        
        //Shader
        m_Shader = std::make_unique<Shader>("resource/shaders/basic/");
        m_Shader->bind();

        //Transform
        //m_Model = glm::rotate(m_Model, 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));

        //Texture
        m_Texture = std::make_unique<Texture>("resource/textures/container.jpg");
        m_Texture->bind(0);
        m_Shader->SetUniform1i("sampler", 0);

        //Renderer
        m_Renderer = std::make_unique<Renderer>();
	}

    SandBox::~SandBox() {}

	void SandBox::onUpdate(float deltaTime) {}

	void SandBox::onRender()
    {
        m_Renderer->clear();        
        m_Shader->bind();        
        //m_Model = glm::translate(glm::mat4(1.0f), translation);
        m_Model = glm::rotate(m_Model, 0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 mvp = camera.GetProjection() * camera.GetView() * m_Model;
        m_Shader->setUniformMat4v("u_Mvp", mvp);
        if (m_FBO)
        {
            m_FBO->bind();
        }
        m_Renderer->clear();
        m_Renderer->drawArray(*m_VAO, *m_Shader, m_VBO->GetCount());
    }

    void SandBox::onImGuiRender()
    {
        ImGui::SliderFloat3("translation", &translation.x, -.5f, 0.5f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f /ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }
    void SandBox::buildFBO(const glm::vec2& viewport)
    {
        if (m_FBO)
        {
            m_FBO.reset();
        }
        m_Viewport = viewport;
        m_FBO = std::make_unique<FrameBuffer>(viewport.x, viewport.y);
    }
}