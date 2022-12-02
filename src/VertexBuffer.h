#pragma once

class VertexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	VertexBuffer(unsigned int count, float size, void* data);
	~VertexBuffer();
	void bind() const;
	void unbind()const;
	inline unsigned int GetCount() const { return m_Count; };
};