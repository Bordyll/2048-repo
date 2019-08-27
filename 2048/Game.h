#pragma once
#include <SFML/Graphics.hpp>
#include "Window.h"

class Game
{
public:
	Game();
	~Game();

	sf::Time GetElapsed();
	void RestartClock();
	void Render();
	void TakeInput();
	void Update();
	bool IsDone();
	Window* GetWindow();
	

private:
	sf::Clock clock;
	sf::Time elapsed;
	float MyElapsed;
	Window MyWindow;
	
};

