#pragma once
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"

class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();
	void addBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout) const;
	void bind()const;
	void unbind() const;
};