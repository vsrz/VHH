#include "scoring.h"
#include "WindowManager.h"
#include <sstream>
#include <SFML\Graphics.hpp>

sf::Font font;
sf::Text points_graphics;

void Scoring::Initialize()
{
	font.loadFromFile("./Resources/Fonts/jokerman.ttf");
	points_graphics.setFont(font);
	points_graphics.setCharacterSize(24);
	points_graphics.setString("0");
}

void Scoring::Draw(unsigned int p_num, int score)
{
	std::stringstream pointsStream;
	pointsStream << score;
	points_graphics.setString(pointsStream.str());

	switch(p_num)
	{
	case 0:
		points_graphics.setPosition(5,5);
		break;

	case 1:
		points_graphics.setPosition(WindowManager::GetSize().x - points_graphics.getGlobalBounds().width - 5,5);
		break;

	case 2:
		points_graphics.setPosition(5,WindowManager::GetSize().y - points_graphics.getGlobalBounds().height - 5);
		break;

	case 3:
		points_graphics.setPosition(WindowManager::GetSize().x - points_graphics.getGlobalBounds().width - 5,WindowManager::GetSize().y - points_graphics.getGlobalBounds().height - 5);
		break;
	}

	WindowManager::Draw(points_graphics);
}