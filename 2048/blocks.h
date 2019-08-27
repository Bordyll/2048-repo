#pragma once
#include <SFML/Graphics.hpp>
#include "Window.h"


enum class Direction
{
	none, left, right, up, down
};

struct block
{
	block(int x, int y, int z) : position(x, y), value(z)
	{
		removed = false;
	}
	sf::Vector2i position;
	int value;
	bool removed;
};

class blocks
{
public:
	blocks(sf::Vector2u windSize);
	~blocks();
	void spawnBlock();
	void combine();
	void move();
	int checkCollision(int i);
	void tick();
	void reset();
	void render(sf::RenderWindow& window);
	void takeInput();
	void lose();
	void checkLose();
	void resetDirection();
	block createBlock(std::vector<block> blocko);
	void combineErase();
	bool isRemoved(block b);

private:
	int size;
	Direction direction;
	std::vector<block> blockBody;
	sf::Vector2u windowSize;
	sf::RectangleShape blockRectangle;
	int blockSize;
	sf::RectangleShape bounds[4];
	sf::Texture texture1;
	sf::Texture texture2;
	sf::Texture texture3;
	sf::Texture texture4;
	sf::Texture texture5;
	sf::Texture texture6;
	sf::Texture texture7;
	sf::Texture texture8;
	sf::Texture texture9;
	sf::Texture texture10;
	sf::Texture texture11;
};

