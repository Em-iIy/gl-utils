#include "Window.hpp"

#include "../lib/emlm/mlm/print/vectorPrint.hpp"


Window::Window() {}

Window::~Window() {}


void			Window::resize_callback(GLFWwindow* window, int x, int y)
{
	(void)x;
	(void)y;
	void	*ptr = glfwGetWindowUserPointer(window);
	if (!ptr)
		return ;
	Window *p_window = static_cast<Window *>(ptr);
	p_window->set_update_flags(Window::SIZE);
}

void				Window::set_update_flags(Flag flag)
{
	_update_flags |= (1 << flag);
}

void				Window::unset_update_flags(Flag flag)
{
	_update_flags &= ~(1 << flag); 
}

bool				Window::get_update_flag(Flag flag) const
{
	return ((_update_flags >> flag) & 1);
}


GLFWwindow			*Window::create_fullscreen_windowed_window()
{
	const GLFWvidmode	*vidmode = glfwGetVideoMode(_monitor);
	glfwWindowHint(GLFW_RED_BITS, vidmode->redBits);
	glfwWindowHint(GLFW_BLUE_BITS, vidmode->blueBits);
	glfwWindowHint(GLFW_GREEN_BITS, vidmode->greenBits);
	glfwWindowHint(GLFW_REFRESH_RATE, vidmode->refreshRate);
	GLFWwindow	*window = glfwCreateWindow(vidmode->width, vidmode->height, _title.c_str(), _monitor, nullptr);
	return (window);
}

GLFWwindow			*Window::create_windowed_window()
{
	GLFWwindow	*window = glfwCreateWindow(_size.x, _size.y, _title.c_str(), nullptr, nullptr);
	return (window);
}

void				Window::create_window(const std::string &title, const mlm::ivec2 &size, Mode mode)
{
	_title = title;
	_size = size;
	_mode = mode;
	_monitor = glfwGetPrimaryMonitor();
	switch (_mode)
	{
	case WINDOWED:
		_window = create_windowed_window();
		break;
	case FULL_SCREEN_WINDOWED:
		_window = create_fullscreen_windowed_window();
		break;
	}
	if (_window == nullptr)
	{
		throw std::runtime_error("GLU: failed to create window!");
	}
	glfwMakeContextCurrent(_window);
	if (!gladLoadGL())
	{
		glfwDestroyWindow(_window);
		throw std::runtime_error("GLU: failed to load GL!");
	}
	glfwSetWindowUserPointer(_window, this);
	glfwSetFramebufferSizeCallback(_window, resize_callback);
	glfwGetWindowPos(_window, &_pos.x, &_pos.y);
}

void				Window::update()
{
	if (get_update_flag(SIZE))
	{
		std::cout << "update size" << std::endl;
		glfwGetFramebufferSize(_window, &_size.x, &_size.y);
		glViewport(0, 0, _size.x, _size.y);
		unset_update_flags(Window::SIZE);
	}
	if (get_update_flag(POSITION))
	{
		glfwSetWindowPos(_window, _pos.x, _pos.y);
		unset_update_flags(POSITION);
	}
}

/*    Setters    */
void				Window::set_size(const mlm::ivec2 &size)
{
	std::cout << "set size" << std::endl;
	_size = size;
	glfwSetWindowSize(_window, _size.x, _size.y);
}

void				Window::set_pos(const mlm::ivec2 &pos)
{
	_pos = pos;
	set_update_flags(POSITION);
}

/*    Getters    */
GLFWwindow			*Window::get_window() const
{
	return (_window);
}

const std::string	&Window::get_title() const
{
	return (_title);
}

const mlm::ivec2	&Window::get_size() const
{
	return (_size);
}

const mlm::ivec2	&Window::get_pos() const
{
	return (_pos);
}

Window::Mode		Window::get_mode() const
{
	return (_mode);
}

void				Window::print(void) const
{
	std::cout << "window:\t" << _window << std::endl;
	std::cout << "monitor:\t" << _monitor << std::endl;
	std::cout << "title:\t" << _title << std::endl;
	std::cout << "size:\t" << _size << std::endl;
	std::cout << "pos:\t" << _pos << std::endl;
}
