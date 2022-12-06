#include <imgui/imgui.h>

#include "SandBox.h"

namespace test {
    SandBox::SandBox(Camera& camera, PointLight& light):m_Viewport({ 0, 0 }), camera(camera),light(light),
        translation(glm::vec3(0.5f, 0.0f, 0.0f)),
        m_Model(glm::translate(glm::mat4(1.0f), translation))
	{
        //Data
        float vertexArray[216] = {
              -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
        };
        unsigned int indices[] = {
            0, 2, 1,
            0, 3, 2
        };

        //VAO
        m_VAO = std::make_unique<VertexArray>();

        //VBO
        m_VBO = std::make_unique<VertexBuffer>(36.0f, 36.0f * 6.0f * sizeof(float), vertexArray);

        //LAYOUT
        VertexBufferLayout layout;
        layout.push<float>(3);
        layout.push<float>(3);
        m_VAO->addBuffer(*m_VBO, layout);

        //Material
        glm::vec3 ambient(0.2, 0.2, 0.2);
        glm::vec3 diffuse(0.5, 0.8, 0.3);
        glm::vec3 specular(0.9, 0.9, 0.9);
        m_Material = std::make_unique<BlinnPhongMaterial>("baseMaterial", ambient, diffuse, specular, 32.0f);
        m_Material->shader->bind();
        //Renderer
        m_Renderer = std::make_unique<Renderer>();
	}

    SandBox::~SandBox() {}

	void SandBox::onUpdate(float deltaTime) {}

	void SandBox::onRender()
    {
        
        glEnable(GL_DEPTH_TEST);
        m_Renderer->clear();          
        m_Material->shader->bind();
        m_Model = glm::rotate(m_Model, 0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 mvp = camera.GetProjection() * camera.GetView() * m_Model;

        m_Material->setUniforms();
        m_Material->shader->setUniformMat4v("u_Mvp", mvp);
        m_Material->shader->setUniformMat4v("u_Model", m_Model);
        m_Material->shader->setUniformMat3v("u_itModel", glm::mat3(glm::transpose(glm::inverse(m_Model))));
        m_Material->shader->setUniform3f("lightColor", light.getColor());
        m_Material->shader->setUniform3f("lightPosition", light.getPosition());
        m_Material->shader->setUniform3f("eyePosition", camera.m_Position);

        if (m_FBO)
        {
            m_FBO->bind();
        }
        m_Renderer->clear();
        m_Renderer->drawArray(*m_VAO, *m_Material->shader, m_VBO->GetCount());
    }

    void SandBox::onImGuiRender()
    {
        ImGui::SliderFloat3("translation", &translation.x, -.5f, 0.5f);
        ImGui::SliderFloat3("lightColor", &light.getColor().x, 0.0, 1.0);
        ImGui::SliderFloat3("lightPostion", &light.getPosition().x, -2.0f, 2.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f /ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        //ImGui::SliderFloat3("diffuseColor", &(m_Material->diffuseColor.x), 0.0f, 1.0f);
        //ImGui::SliderFloat3("specularColor", &(m_Material->specularColor.x), 0.0f, 1.0f);
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