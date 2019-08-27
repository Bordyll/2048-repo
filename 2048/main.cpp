#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "blocks.h"
#include "Game.h"
#include "Window.h"

Window window;
Game game;
blocks blocky(window.GetWindowSize());

int main()
{
	while (game.IsDone() == false)
	{
		blocky.takeInput(); 
		game.Update(); 
		blocky.tick();
		blocky.render(*game.GetWindow()->GetRenderWindow());
		blocky.resetDirection();
	}

}