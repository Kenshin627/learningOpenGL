#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "FrameBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"
#include "Camera.h"
#include "Lights/PointLight.h"
#include "Materials/BlinnPhongBaseMaterial.h"

namespace test {
	class SandBox
	{
	private:
		std::unique_ptr<FrameBuffer> m_FBO;
		std::unique_ptr<IndexBuffer> m_IBO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<VertexArray> m_VAO;
		//std::unique_ptr<Shader> m_Shader; 
		std::unique_ptr<Texture> m_Texture;
		std::unique_ptr<Renderer> m_Renderer;
		std::unique_ptr<BlinnPhongMaterial> m_Material;

		glm::vec3 translation;
		glm::mat4 m_Proj, m_View, m_Model;

		glm::vec2 m_Viewport;
		Camera& camera;
		PointLight& light;
		
	public:
		SandBox(Camera& camera, PointLight& light);
		~SandBox();
	public:
		void onUpdate(float deltaTime);
		void onRender();
		void onImGuiRender();
		void buildFBO(const glm::vec2& viewport);
		inline FrameBuffer& getFBO() const { return *m_FBO; };
	};
}