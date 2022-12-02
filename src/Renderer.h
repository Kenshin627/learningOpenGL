#pragma once

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer
{
public:
	void drawElements(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const;
	void drawArray(const VertexArray& vao, const Shader& shader, unsigned int count) const;
	void clear() const;
};