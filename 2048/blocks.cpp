#include "blocks.h"
#include "iostream"


blocks::blocks(sf::Vector2u windSize)
{
	texture1.loadFromFile("2.png");
	texture2.loadFromFile("4.png");
	texture3.loadFromFile("8.png");
	texture4.loadFromFile("16.png");
	texture5.loadFromFile("32.png");
	texture6.loadFromFile("64.png");
	texture7.loadFromFile("128.png");
	texture8.loadFromFile("256.png");
	texture9.loadFromFile("512.png");
	texture10.loadFromFile("1024.png");
	texture11.loadFromFile("2048.png");
	windowSize = windSize;
	size = 150;
	blockRectangle.setSize(sf::Vector2f(size - 1, size - 1));
	for (int i = 0; i < 4; ++i)
	{
		bounds[i].setFillColor(sf::Color(150, 0, 0));
		if (!((i + 1) % 2))
		{
			bounds[i].setSize(sf::Vector2f(windowSize.x, blockSize));
		}
		else
		{
			bounds[i].setSize(sf::Vector2f(blockSize, windowSize.y));
		}
		if (i < 2)
		{
			bounds[i].setPosition(0, 0);
		}
		else
		{
			bounds[i].setOrigin(bounds[i].getSize());
			bounds[i].setPosition(sf::Vector2f(windowSize));
		}
	}
	reset();
	blockBody.push_back(block(0, 0, 2));
}

blocks::~blocks()
{
}

//creates new block
void blocks::spawnBlock()
{
	std::vector<block> all;
	for (int i = 3; i >= 0; --i)
	{
		for (int j = 3; j >= 0; --j)
		{
			all.push_back(block(i, j, 2));
		}
	}
	for (int i = blockBody.size() - 1; i >= 0; --i)
	{
		
		for (int j = all.size() - 1; j >= 0; --j)
		{
			if (blockBody[i].position == all[j].position)
			{
				all.erase(all.begin() + j);
			}
		}
	}
	blockBody.push_back(createBlock(all));
}

block blocks::createBlock(std::vector<block> blocko)
{
	int random = rand() % blocko.size();
	return blocko[random];
}

// moves, checks collision and combines
void blocks::move()
{
	std::vector<int> y;
	std::vector<int> x;
	if (direction == Direction::up)
	{
		for (int i = 0; i <= blockBody.size() - 1; i++)
		{
			int yV = checkCollision(i);
			y.push_back(0 + yV);
		}
		for (int i = 0; i <= blockBody.size() - 1; i++)
		{
			blockBody[i].position.y = y[i];
		}
		y.clear();
		combine();
	}
	if (direction == Direction::down)
	{
		for (int i = 0; i <= blockBody.size() - 1; i++)
		{
			int yV = checkCollision(i);
			y.push_back(3 + yV);
		}
		for (int i = 0; i <= blockBody.size() - 1; i++)
		{
			blockBody[i].position.y = y[i];
		}
		y.clear();
		combine();
	}
	if (direction == Direction::left)
	{
		for (int i = 0; i <= blockBody.size() - 1; i++)
		{
			int xV = checkCollision(i);
			x.push_back(0 + xV);
		}
		for (int i = 0; i <= blockBody.size() - 1; i++)
		{
			blockBody[i].position.x = x[i];
		}
		x.clear();
		combine();
	}
	if (direction == Direction::right)
	{
		for (int i = 0; i <= blockBody.size() - 1; i++)
		{
			int xV = checkCollision(i);
			x.push_back(3 + xV);
		}
		for (int i = 0; i <= blockBody.size() - 1; i++)
		{
			blockBody[i].position.x = x[i];
		}
		x.clear();
		combine();
	}
	std::cout << std::endl;
} 

int blocks::checkCollision(int i)
{
	int x = 0;
	int y = 0;
	if (direction == Direction::up)
	{
		for (int j = blockBody.size() - 1; j >= 0; --j)
		{
			if (blockBody[i].position.x == blockBody[j].position.x && blockBody[i].position != blockBody[j].position)
			{
				if (blockBody[i].position.y > blockBody[j].position.y)
				{
					++y;
				}
			}
		}
		return y;
	}
	if (direction == Direction::down)
	{
		for (int j = blockBody.size() - 1; j >= 0; --j)
		{
			if (blockBody[i].position.x == blockBody[j].position.x && blockBody[i].position != blockBody[j].position)
			{
				if (blockBody[i].position.y < blockBody[j].position.y)
				{
					--y;
				}
			}
		}
		return y;
	}
	if (direction == Direction::left)
	{
		for (int j = blockBody.size() - 1; j >= 0; --j)
		{
			if (blockBody[i].position.y == blockBody[j].position.y && blockBody[i].position != blockBody[j].position)
			{
				if (blockBody[i].position.x > blockBody[j].position.x)
				{
					++x;
				}
			}
		}
		return x;
	}
	if (direction == Direction::right)
	{
		for (int j = blockBody.size() - 1; j >= 0; --j)
		{
			if (blockBody[i].position.y == blockBody[j].position.y && blockBody[i].position != blockBody[j].position)
			{
				if (blockBody[i].position.x < blockBody[j].position.x)
				{
					--x;
				}
			}
		}
		return x;
	}
}

void blocks::combine()
{
	if (direction == Direction::up)
	{
		for (int i = blockBody.size() - 1; i >= 0; --i)
		{
			for (int j = blockBody.size() - 1; j >= 0; --j)
			{
				if (blockBody[i].position.x == blockBody[j].position.x && blockBody[i].position.y == blockBody[j].position.y - 1 && blockBody[j].value == blockBody[i].value)
				{
					blockBody[i].value = blockBody[i].value * 2;
					blockBody[j].removed = true;
				}
			}
		}
	}
	if (direction == Direction::down)
	{
		for (int i = blockBody.size() - 1; i >= 0; --i)
		{
			for (int j = blockBody.size() - 1; j >= 0; --j)
			{
				if (blockBody[i].position.x == blockBody[j].position.x && blockBody[i].position.y == blockBody[j].position.y + 1 && blockBody[j].value == blockBody[i].value)
				{
					blockBody[i].value = blockBody[i].value * 2;
					blockBody[j].removed = true;
				}
			}
		}
	}
	if (direction == Direction::left)
	{
		for (int i = blockBody.size() - 1; i >= 0; --i)
		{
			for (int j = blockBody.size() - 1; j >= 0; --j)
			{
				if (blockBody[i].position.y == blockBody[j].position.y && blockBody[i].position.x == blockBody[j].position.x - 1 && blockBody[j].value == blockBody[i].value)
				{
					blockBody[i].value = blockBody[i].value * 2;
					blockBody[j].removed = true;
				}
			}
		}
	}
	if (direction == Direction::right)
	{
		for (int i = blockBody.size() - 1; i >= 0; --i)
		{
			for (int j = blockBody.size() - 1; j >= 0; --j)
			{
				if (blockBody[i].position.y == blockBody[j].position.y && blockBody[i].position.x == blockBody[j].position.x + 1 && blockBody[j].value == blockBody[i].value)
				{
					blockBody[i].value = blockBody[i].value * 2;
					blockBody[j].removed = true;
				}
			}
		}
	}
	combineErase();
	for (int i = blockBody.size() - 1; i >= 0; --i)
	{
		blockBody[i].removed = false;
	}
}

void blocks::combineErase()
{
	blockBody.erase(std::remove_if(blockBody.begin(), blockBody.end(), [](block b) {return b.removed; }), blockBody.end());
}

bool blocks::isRemoved(block b)
{
	return b.removed;
}

//takes input
void blocks::takeInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		direction = Direction::up;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		direction = Direction::down;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		direction = Direction::left;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		direction = Direction::right;
	}
}

//resets direction
void blocks::resetDirection()
{
	if (direction != Direction::none)
	{
		direction = Direction::none;
		sf::sleep(sf::seconds(0.2));
	}
}

//checks to see if lost, and if so loses and resets
void blocks::checkLose()
{
	if (blockBody.size() == 16)
	{
		lose();
	}
}

void blocks::lose()
{
	reset();
}

void blocks::reset()
{
	blockBody.clear();
}

//checks to see if input is taken, then carries out game
void blocks::tick()
{
	if (direction != Direction::none)
	{
		
		move();
		checkLose();
		spawnBlock();

	}
}

//renders
void blocks::render(sf::RenderWindow& window)
{
	window.clear();
	for (int i = blockBody.size() - 1; i >= 0; --i)
	{
		blockRectangle.setFillColor(sf::Color::White);
		blockRectangle.setPosition(blockBody[i].position.x * size, blockBody[i].position.y * size);
		if (blockBody[i].value == 2)
		{
			blockRectangle.setTexture(&texture1);
		}
		if (blockBody[i].value == 4)
		{
			blockRectangle.setTexture(&texture2);
		}
		if (blockBody[i].value == 8)
		{
			blockRectangle.setTexture(&texture3);
		}
		if (blockBody[i].value == 16)
		{
			blockRectangle.setTexture(&texture4);
		}
		if (blockBody[i].value == 32)
		{
			blockRectangle.setTexture(&texture5);
		}
		if (blockBody[i].value == 64)
		{
			blockRectangle.setTexture(&texture6);
		}
		if (blockBody[i].value == 128)
		{
			blockRectangle.setTexture(&texture7);
		}
		if (blockBody[i].value == 256)
		{
			blockRectangle.setTexture(&texture8);
		}
		if (blockBody[i].value == 512)
		{
			blockRectangle.setTexture(&texture9);
		}
		if (blockBody[i].value == 1024)
		{
			blockRectangle.setTexture(&texture10);
		}
		if (blockBody[i].value == 2048)
		{
			blockRectangle.setTexture(&texture11);
		}
		if (blockBody[i].position == blockBody.back().position)
		{
			blockRectangle.setFillColor(sf::Color::Green); 
		}
		window.draw(blockRectangle);
	}
	for (int i = 0; i < 4; ++i)
	{
		window.draw(bounds[i]);
	}
	window.display();
}
