#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Test.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"
#include <Renderer.h>

namespace test {
	class TestTexture :public Test
	{
	private:
		std::unique_ptr<IndexBuffer> m_IBO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<Shader> m_Shader; 
		std::unique_ptr<Texture> m_Texture;
		std::unique_ptr<Renderer> m_Renderer;

		glm::vec3 translation;
		glm::mat4 m_Proj, m_View, m_Model;
		
	public:
		TestTexture();
		~TestTexture();
	public:
		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
	};
}