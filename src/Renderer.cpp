#include "Renderer.h"

void Renderer::draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const
{
	shader.bind();
	vao.bind();
	ibo.bind();
	glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::clear() const
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}