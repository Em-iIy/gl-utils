/*
Created by: Emily (Em_iIy) Winnink
Created on: 16/01/2025
*/

#include "FrameBuffer.hpp"

FrameBuffer::FrameBuffer(): _id(0), _width(0), _height(0), _depthTexture(0), _depthRbo(0)
{}

FrameBuffer::~FrameBuffer()
{
	destroy();
}

void	FrameBuffer::create(int width, int height)
{
	destroy();

	_width = width;
	_height = height;
	glGenFramebuffers(1, &_id);
}

void	FrameBuffer::destroy()
{
	if (_id != 0)
	{
		glDeleteFramebuffers(1, &_id);
		_id = 0;
	}

	for (GLuint texture : _colorTextures)
		if (texture)
			glDeleteTextures(1, &texture);
	_colorTextures.clear();

	if (_depthTexture != 0)
	{
		glDeleteTextures(1, &_depthTexture);
		_depthTexture = 0;
	}

	if (_depthRbo != 0)
	{
		glDeleteRenderbuffers(1, &_depthRbo);
		_depthRbo = 0;
	}
}

void	FrameBuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, _id);
}

void	FrameBuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void	FrameBuffer::attachColorTexture(int index, GLenum internalFormat, GLenum format, GLenum type, bool nearest, bool clamp, bool mipmap)
{
	if (_id == 0)
		throw std::runtime_error("Framebuffer hasn't been created");
	
	if (static_cast<int>(_colorTextures.size()) <= index)
		_colorTextures.resize(index + 1, 0);
	
	if (_colorTextures[index] == 0)
		glGenTextures(1, &_colorTextures[index]);
	glBindTexture(GL_TEXTURE_2D, _colorTextures[index]);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, _width, _height, 0, format, type, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, nearest ? GL_NEAREST : GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, nearest ? GL_NEAREST : GL_LINEAR);

	if (mipmap)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, nearest ? GL_NEAREST_MIPMAP_NEAREST : GL_LINEAR_MIPMAP_LINEAR);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, clamp ? GL_CLAMP_TO_EDGE : GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, clamp ? GL_CLAMP_TO_EDGE : GL_REPEAT);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, _colorTextures[index], 0);
}

void	FrameBuffer::ensureDepthTexture(GLenum internalFormat)
{
	if (_id == 0)
		throw std::runtime_error("Framebuffer hasn't been created");
	
	if (_depthRbo != 0)
	{
		glDeleteRenderbuffers(1, &_depthRbo);
		_depthRbo = 0;
	}
	if (_depthTexture)
		glGenTextures(1, &_depthTexture);
	
	glBindTexture(GL_TEXTURE_2D, _depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, _width, _height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthTexture, 0);
}

void	FrameBuffer::ensureDepthRbo(GLenum internalFormat)
{
	if (_id == 0)
		throw std::runtime_error("Framebuffer hasn't been created");
	
	if (_depthTexture != 0)
	{
		glDeleteTextures(1, &_depthTexture);
		_depthTexture = 0;
	}
	if (_depthRbo == 0)
		glGenRenderbuffers(1, &_depthRbo);
	
	glBindRenderbuffer(GL_RENDERBUFFER, _depthRbo);
	glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, _width, _height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	if (internalFormat == GL_DEPTH24_STENCIL8)
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _depthRbo);
	else
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthRbo);
}

bool	FrameBuffer::checkStatus() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, _id);
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cerr << "Framebuffer not complete: 0x" << std::hex << status << std::endl;
		return (false); 
	}
	return (true); 
}

void	FrameBuffer::setDrawBuffers(const std::vector<GLenum> &drawBuffers)
{
	glDrawBuffers(static_cast<GLsizei>(drawBuffers.size()), drawBuffers.empty() ? nullptr : drawBuffers.data());
}

void	FrameBuffer::blitDepthFrom(GLuint srcFbo, int srcWidth, int srcHeight)
{
	if (_id == 0)
		throw std::runtime_error("Dst Framebuffer hasn't been created");
	if (_depthTexture == 0 && _depthRbo == 0)
		throw std::runtime_error("Dst Framebuffer has no depth attachment");

	glBindFramebuffer(GL_READ_FRAMEBUFFER, srcFbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _id);

	glBlitFramebuffer(0, 0, srcWidth, srcHeight, 0, 0, _width, _height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void	FrameBuffer::clear(bool clearColor, bool clearDepth, const mlm::vec4 clearColorRGBA)
{
	GLbitfield mask = 0;
	if (clearColor)
	{
		glClearColor(clearColorRGBA.x, clearColorRGBA.y, clearColorRGBA.z, clearColorRGBA.w);
		mask |= GL_COLOR_BUFFER_BIT;
	}
	if (clearDepth)
		mask |= GL_DEPTH_BUFFER_BIT;
	if (mask)
		glClear(mask);
}

void	FrameBuffer::resize(int newWidth, int newHeight)
{
	if (newWidth == _width && newHeight == _height)
		return ;
	_width = newWidth;
	_height = newHeight;

	for (GLuint texture : _colorTextures)
	{
		if (texture != 0)
		{
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		}
	}

	if (_depthTexture != 0)
	{
		glBindTexture(GL_TEXTURE_2D, _depthTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, _width, _height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, nullptr);
	}

	if (_depthRbo != 0)
	{
		glBindRenderbuffer(GL_RENDERBUFFER, _depthRbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}
}

GLuint	FrameBuffer::getColorTexture(int index) const
{
	if (index < 0 || index >= static_cast<int>(_colorTextures.size()))
		return (0);
	return (_colorTextures[index]);
}

GLuint	FrameBuffer::getDepthTexture() const
{
	return (_depthTexture);
}

GLuint	FrameBuffer::getId() const
{
	return (_id);
}

int	FrameBuffer::getWidth() const
{
	return (_width);
}

int	FrameBuffer::getHeight() const
{
	return (_height);
}
