#include "Window.h"
#include <SFML/Graphics.hpp>


Window::Window()
{
}
Window::Window(const std::string& title, const sf::Vector2u& size)
{
	Setup(title, size);
}
Window::~Window()
{
	Destroy();
}

sf::RenderWindow* Window::GetRenderWindow()
{
	return &MyWindow;
}

void Window::Setup(const std::string title, const sf::Vector2u& size)
{
	MyWindowTitle = title;
	MyWindowSize = size;
	MyIsFullscreen = false;
	MyIsDone = false;
	Create();
}

void Window::Draw(sf::Drawable& drawable)
{
	MyWindow.draw(drawable);
}

bool Window::IsDone()
{
	return MyIsDone;
}
bool Window::IsFullscreen()
{
	return MyIsFullscreen;
}

void Window::BeginDraw()
{
	MyWindow.clear();
}

void Window::EndDraw()
{
	MyWindow.display();
}

void Window::Destroy()
{
	MyWindow.close();
}
void Window::Create()
{
	auto style = (MyIsFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	MyWindow.create({ MyWindowSize.x, MyWindowSize.y }, MyWindowTitle, style);
}

void Window::Update()
{
	sf::Event event;
	while (MyWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			MyIsDone = true;
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F11)
		{
			ToggleFullscreen();
		}
	}
}

void Window::ToggleFullscreen()
{
MyIsFullscreen = !MyIsFullscreen;
Destroy();
Create();
}

sf::Vector2u Window::GetWindowSize()
{
	return MyWindowSize;
}

