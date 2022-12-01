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

namespace test {
	class SandBox
	{
	private:
		std::unique_ptr<FrameBuffer> m_FBO;
		std::unique_ptr<IndexBuffer> m_IBO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<Shader> m_Shader; 
		std::unique_ptr<Texture> m_Texture;
		std::unique_ptr<Renderer> m_Renderer;

		glm::vec3 translation;
		glm::mat4 m_Proj, m_View, m_Model;

		glm::vec2 m_Viewport;
		
	public:
		SandBox();
		~SandBox();
	public:
		void onUpdate(float deltaTime);
		void onRender();
		void onImGuiRender();
		void buildFBO(const glm::vec2& viewport);
		inline FrameBuffer& getFBO() const { return *m_FBO; };
	};
}