#include "Renderer.h"

void Renderer::drawElements(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const
{
	shader.bind();
	vao.bind();
	ibo.bind();
	glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::drawArray(const VertexArray& vao, const Shader& shader, unsigned int count) const
{
	shader.bind();
	vao.bind();
	glDrawArrays(GL_TRIANGLES, 0, count);
}

void Renderer::clear() const
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}