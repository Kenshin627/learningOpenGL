#include "VertexArray.h"

VertexArray::VertexArray() 
{
	glGenVertexArrays(1, &m_RendererID);
}
VertexArray::~VertexArray() 
{
	glDeleteVertexArrays(1, &m_RendererID);
}
void VertexArray::addBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout) const
{
	bind();
	vbo.bind();
	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	for (int i = 0; i < elements.size(); i++)
	{		
		auto& element = elements[i];
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (void*)offset);
		offset += element.count * VertexBufferLayoutElement::GetSizeofType(element.type);
		glEnableVertexAttribArray(i);
	}
}

void VertexArray::bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}