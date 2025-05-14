/*
Created by: Emily (Em_iIy) Winnink
Created on: 07/09/2024
*/
#pragma once

#include <string>

#include "read_file.hpp"
#include "../../lib/emlm/emlm.hpp"

class Shader {
	public:
		unsigned int id;
	
		Shader();
		Shader(const char *vertex_file_name, const char *fragment_file_name);
		~Shader();
		void	load(const char *vertex_source, const char *fragment_source);
		void	use();
		void	del();
		void	set_bool(const std::string &name, bool value) const;
		void	set_float(const std::string &name, float value) const;
		void	set_int(const std::string &name, int value) const;
		void	set_vec2(const std::string &name, const mlm::vec2 &value) const;
		void	set_vec3(const std::string &name, const mlm::vec3 &value) const;
		void	set_mat4(const std::string &name, mlm::mat4 &value) const;
};
