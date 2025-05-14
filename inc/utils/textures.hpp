/*
Created by: Emily (Em_iIy) Winnink
Created on: 09/09/2024
*/
#pragma once

#include <iostream>

#include "../bmp/bmp.h"

uint	load_texture(const char *img);
void	delete_texture(uint texture);

class Tex2d	{
	private:
		GLuint	id;

		GLint	wrap_s;
		GLint	wrap_t;
		GLint	filter_min;
		GLint	filter_mag;

		GLint	format;
	public:
		Tex2d();
		Tex2d(GLenum wrap, GLenum filter);
		~Tex2d();

		void	load(const char *img);
		void	load(const bmp_t &bmp);
		void	load(const std::string &img);
		void	load_render_texture(GLsizei width, GLsizei height, GLenum format, GLenum type);
		
		const GLuint	&get_id() const;

		void	bind();
		void	del();
};
