#pragma once

class IndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	IndexBuffer(unsigned int count, unsigned int* data);
	~IndexBuffer();
	void bind() const;
	void unbind() const;
	unsigned int getCount() const;
};