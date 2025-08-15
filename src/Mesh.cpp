/*
Created by: Emily (Em_iIy) Winnink
Created on: 21/07/2025
*/

#include <cstddef>

#include "Mesh.hpp"

Mesh::Mesh() {}

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices): _vertices(vertices), _indices(indices)
{
	setup_mesh();
}

void	Mesh::draw(Shader &shader)
{
	(void)shader;
	_vao.bind();
	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
	_vao.unbind();
}


void	Mesh::setup_mesh()
{
	_vao.init();
	_vao.bind();

	// Setup index buffer
	_ebo = EBO(_indices);

	// Setup Vertex buffer
	_vbo = VBO(reinterpret_cast<GLfloat *>(_vertices.data()), static_cast<GLsizeiptr>(_vertices.size() * sizeof(Vertex)));
	_vao.link_attr(_vbo, 0, sizeof(Vertex::pos) / sizeof(GLfloat), GL_FLOAT, sizeof(Vertex), (void *)offsetof(Vertex, pos));
	_vao.link_attr(_vbo, 1, sizeof(Vertex::normal) / sizeof(GLfloat), GL_FLOAT, sizeof(Vertex), (void *)offsetof(Vertex, normal));
	_vao.link_attr(_vbo, 2, sizeof(Vertex::texUV) / sizeof(GLfloat), GL_FLOAT, sizeof(Vertex), (void *)offsetof(Vertex, texUV));

	_vao.unbind();
	_vbo.unbind();
}