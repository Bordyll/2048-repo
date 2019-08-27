#include "Game.h"
#include <SFML/Graphics.hpp>
#include "Window.h"
#include <iostream>

Game::Game() :
	MyWindow("2064", sf::Vector2u(600,600))
{
}

Game::~Game()
{
}


void Game::TakeInput()
{
}


void Game::Render()
{
	MyWindow.BeginDraw();
	MyWindow.EndDraw();
}


void Game::Update()
{
	MyWindow.Update();
}



bool Game::IsDone()
{
	return MyWindow.IsDone();
}

void Game::RestartClock()
{
	MyElapsed += clock.restart().asSeconds();
}

sf::Time Game::GetElapsed()
{
	return elapsed;
}


Window* Game::GetWindow() { return &MyWindow; }