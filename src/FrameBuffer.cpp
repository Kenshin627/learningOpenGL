#include <GL/glew.h>
#include <iostream>

#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(unsigned int width, unsigned int height):viewport_Width(width), viewport_Height(height)
{
	glGenFramebuffers(1, &m_RendererID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
	TextureAttachment();
	RenderBufferAttachment();
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "[ERROR]: FRAME BUFFER initialize error!";
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &m_RendererID);
	glDeleteTextures(1, &m_RenderTextureID);
	glDeleteRenderbuffers(1, &m_RenderBufferID);
}

void FrameBuffer::bind() const
{
	glViewport(0, 0, viewport_Width, viewport_Height);
	glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
}

void FrameBuffer::unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glDeleteFramebuffers(1, &m_RendererID);
	//glDeleteTextures(1, &m_RenderTextureID);
	//glDeleteRenderbuffers(1, &m_RenderBufferID);
}

void FrameBuffer::TextureAttachment()
{
	glGenTextures(1, &m_RenderTextureID);
	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, m_RenderTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, viewport_Width, viewport_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_RenderTextureID, 0);
}

void FrameBuffer::RenderBufferAttachment()
{
	glGenRenderbuffers(1, &m_RenderBufferID);
	glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBufferID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, viewport_Width, viewport_Height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderBufferID);
	//glGenTextures(1, &m_RenderBufferID);
	//glBindTexture(GL_TEXTURE_2D, m_RenderBufferID);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, viewport_Width, viewport_Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_RenderBufferID, 0);
}