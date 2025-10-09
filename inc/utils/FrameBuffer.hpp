/*
Created by: Emily (Em_iIy) Winnink
Created on: 16/01/2025
*/
#pragma once

#include <vector>

#include "../GLAD/glad.h"
#include "../../gl-utils.hpp"


// class FrameBuffer {
// 	public:
// 		GLuint			id = {};
// 		GLsizei 		width;
// 		GLsizei 		height;
// 		Tex2d			render_texture;
// 		RenderBuffer	render_buffer;

// 		FrameBuffer();
// 		void	generate(GLsizei in_width, GLsizei in_height);
// 		void	bind();
// 		void	unbind();
// 		void	del();

// 		void	link_render_texture(GLenum attachment);
// 		void	link_render_buffer(RenderBuffer &rbo);
// 		bool	check_status();
// };

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
			GLenum internalFormat = GL_DEPTH_COMPONENT24
		);

		void				ensureDepthRbo(
			GLenum internalFormat = GL_DEPTH24_STENCIL8
		);

		bool				checkStatus() const;

		void				setDrawBuffers(const std::vector<GLenum> &drawBuffers);

		void				blitDepthFrom(GLuint srcFbo, int srcWidth, int srcHeight);

		void				clear(bool clearColor, bool clearDepth, const mlm::vec4 clearColorRGBA) const;

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
