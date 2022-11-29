#pragma once

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer
{
public:
	void draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const;
	void clear() const;
};