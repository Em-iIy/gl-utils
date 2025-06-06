/*
Created by: Emily (Em_iIy) Winnink
Created on: 07/09/2024
*/

#include <iostream>

#include "VBO.hpp"

VBO::VBO(void)
{
}

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	glGenBuffers(1, &this->id);
	glBindBuffer(GL_ARRAY_BUFFER, this->id);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

// Binds the VBO
void VBO::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->id);
}

// Unbinds the VBO
void VBO::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Deletes the VBO
void VBO::del()
{
	glDeleteBuffers(1, &this->id);
}
