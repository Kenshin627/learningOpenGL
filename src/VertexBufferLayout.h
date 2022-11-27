#pragma once
#include <GL/glew.h>
#include <vector>

struct VertexBufferLayoutElement
{
	unsigned int count;
	unsigned int type;
	unsigned char normalized;
	static unsigned int GetSizeofType(const unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:          return 4;
			case GL_UNSIGNED_INT:   return 4;
			case GL_UNSIGNED_BYTE : return 1;
		}
		return 0;
	}
};

class VertexBufferLayout
{
	private:
		std::vector<VertexBufferLayoutElement> elements;
		unsigned int m_Stride;
	public:
		VertexBufferLayout():m_Stride(0) {}
		~VertexBufferLayout() {}

		template<typename T>
		void push(unsigned int count)
		{
			
		}

		template<>
		void push<float>(unsigned int count)
		{
			elements.push_back({ count, GL_FLOAT, GL_FALSE });
			m_Stride += VertexBufferLayoutElement::GetSizeofType(GL_FLOAT) * count;
		}

		template<>
		void push<unsigned int>(unsigned int count)
		{
			elements.push_back({ count, GL_UNSIGNED_INT, GL_FALSE });
			m_Stride += VertexBufferLayoutElement::GetSizeofType(GL_UNSIGNED_INT) * count;
		}

		template<>
		void push<unsigned char>(unsigned int count)
		{
			elements.push_back({ count, GL_UNSIGNED_BYTE, GL_TRUE });
			m_Stride += VertexBufferLayoutElement::GetSizeofType(GL_UNSIGNED_BYTE) * count;
		}

		inline const std::vector<VertexBufferLayoutElement>& getElements() const { return elements; }

		inline const unsigned int getStride() const { return m_Stride; }

};