#pragma once

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(unsigned int size, void* data);
	~VertexBuffer();
	void bind() const;
	void unbind()const;
};