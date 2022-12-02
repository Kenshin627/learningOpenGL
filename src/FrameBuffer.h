#pragma once
class FrameBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_RenderTextureID;
	unsigned int m_RenderBufferID;
	unsigned int viewport_Width;
	unsigned int viewport_Height;
public:
	FrameBuffer(unsigned int width, unsigned int height);
	~FrameBuffer();
	void bind() const;
	void unbind() const;
	void TextureAttachment();
	void RenderBufferAttachment();
	inline unsigned int GetTextureID() const { return m_RenderTextureID; };
};