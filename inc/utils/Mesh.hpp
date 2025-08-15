/*
Created by: Emily (Em_iIy) Winnink
Created on: 21/07/2025
*/

#pragma once

#include <vector>

#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "Shader.hpp"

#include "../../lib/emlm/emlm.hpp"

struct Vertex {
	mlm::vec3 pos;
	mlm::vec3 normal;
	mlm::vec2 texUV;
};

class Mesh {
	public:
		std::vector<Vertex>		_vertices;
		std::vector<uint32_t>	_indices;
		Mesh();
		Mesh(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices);

		void	draw(Shader &shader);
	
	private:
		VAO		_vao;
		VBO		_vbo;
		EBO		_ebo;

		void	setup_mesh();
};
