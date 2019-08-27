#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Window
{


public:
	Window();
	Window(const std::string& title, const sf::Vector2u& size);
	~Window();
	void BeginDraw();
	void EndDraw();

	void Update();
	bool IsDone();
	bool IsFullscreen();
	sf::Vector2u GetWindowSize();
	


	void ToggleFullscreen();
	void Draw(sf::Drawable & drawable);

	sf::RenderWindow* GetRenderWindow();

private:
	void Setup(const std::string title, const sf::Vector2u& size);
	void Destroy();
	void Create();

	
	sf::RenderWindow MyWindow;
	sf::Vector2u MyWindowSize;
	std::string MyWindowTitle;
	bool MyIsDone;
	bool MyIsFullscreen;

};

