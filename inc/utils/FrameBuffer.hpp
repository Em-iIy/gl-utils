/*
Created by: Emily (Em_iIy) Winnink
Created on: 16/01/2025
*/
#pragma once

#include <vector>

#include "../GLAD/glad.h"
#include "../../gl-utils.hpp"


class FrameBuffer {
	public:
		FrameBuffer();
		~FrameBuffer();
	
		void				create(int width, int height);
		void				destroy();

		void				bind();
		static void			unbind();

		void				attachColorTexture(
			int index = 0,
			GLenum internalFormat = GL_RGBA8,
			GLenum format = GL_RGBA,
			GLenum type = GL_UNSIGNED_BYTE,
			bool nearest = true,
			bool clamp = true,
			bool mipmap = false
		);

		void				ensureDepthTexture(
			GLenum internalFormat = GL_DEPTH_COMPONENT24,
			GLenum type = GL_UNSIGNED_INT,
			bool nearest = true,
			GLenum clamp = GL_CLAMP_TO_EDGE,
			mlm::vec4 borderColor = mlm::vec4(1.0f)
		);

		void				ensureDepthRbo(
			GLenum internalFormat = GL_DEPTH24_STENCIL8
		);

		bool				checkStatus() const;

		void				setDrawBuffers(const std::vector<GLenum> &drawBuffers);

		// UNBINDS CURRENT FBO
		// DON'T FORGET TO REBIND
		void				blitDepthFrom(GLuint srcFbo, int srcWidth, int srcHeight);

		static void			clear(bool clearColor, bool clearDepth, const mlm::vec4 clearColorRGBA);
		static void			clearBufferfv(GLenum buffer, GLint index, const mlm::vec4 clearColorRGBA);

		void				resize(int newWidth, int newHeight);

		GLuint				getColorTexture(int index = 0) const;
		GLuint				getDepthTexture() const;
		GLuint				getId() const;
		int					getWidth() const;
		int					getHeight() const;

	private:
		GLuint				_id;
		GLsizei				_width;
		GLsizei				_height;
		std::vector<GLuint>	_colorTextures;
		GLuint				_depthTexture;
		GLuint				_depthRbo;
};
