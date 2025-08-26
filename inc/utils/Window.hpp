#pragma once

#include "../GLAD/glad.h"
#include "../GLFW/glfw3.h"
#include "../../gl-utils.hpp"

class Window
{
	public:
		enum	Mode {
			WINDOWED,
			FULL_SCREEN_WINDOWED
		};

		enum	Flag {
			SIZE,
			POSITION 
		};

	private:
		GLFWwindow	*_window = nullptr;
		GLFWmonitor *_monitor = nullptr;
		std::string	_title = "default";
		mlm::ivec2	_size = mlm::ivec2(1);
		mlm::ivec2	_pos = mlm::ivec2(0);
		float		_last_frame = 0.0f;
		float		_delta_time = 0.0f;
		uint8_t		_update_flags = 0b00000000;
		// bool		_vsync = true;

		Mode		_mode = WINDOWED;

		GLFWwindow			*create_fullscreen_windowed_window();
		GLFWwindow			*create_windowed_window();
		
		void				update_delta_time();


	public:

		void				set_update_flags(Flag flag);
		void				unset_update_flags(Flag flag);
		bool				get_update_flag(Flag flag) const;
		Window();
		~Window();

		void				create_window(const std::string &title, const mlm::ivec2 &size, Mode mode);

		static void			resize_callback(GLFWwindow* window, int x, int y);

		void				update();


		/*    Setters    */
		void				set_size(const mlm::ivec2 &size);
		void				set_pos(const mlm::ivec2 &pos);

		/*    Getters    */
		GLFWwindow			*get_window() const;
		const std::string	&get_title() const;
		const mlm::ivec2	&get_size() const;
		const mlm::ivec2	&get_pos() const;
		Window::Mode		get_mode() const;
		float				get_delta_time() const;

		void				print(void) const;

};