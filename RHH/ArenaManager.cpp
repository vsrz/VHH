#include "ArenaManager.h"
#include "axisalignedbox.h"
#include "circle.h"
#include <SFML/Graphics/Sprite.hpp>
#include "WindowManager.h"
#include <SFML/Graphics/Texture.hpp>

float Clamp(float value, float min, float max)
{
	if(value < min) return min;
	else if(value > max) return max;

	return value;
}

static Collision::AxisAlignedBox bounding_box(0,0,0);
static sf::Sprite sprite;
static sf::Texture background;
static bool initialized = false;

void ArenaManager::Initialize()
{
	if(initialized)
		return;

	background.loadFromFile("./Resources/Images/arena_bg.png");
	sprite.setTexture(background);

	bounding_box.SetPositionX(background.getSize().x / 2.0f);
	bounding_box.SetPositionY(background.getSize().y / 2.0f);
	bounding_box.SetSizeX(580);
	bounding_box.SetSizeY(370);

	initialized = true;
}

void ArenaManager::ClampInside(Collision::Circle& circle)
{
	circle.SetPositionX(Clamp(circle.GetPositionX(), 30 + circle.GetRadius(), 610 - circle.GetRadius()));
	circle.SetPositionY(Clamp(circle.GetPositionY(), 85 + circle.GetRadius(), 460 - circle.GetRadius()));
}

void ArenaManager::Draw()
{
	WindowManager::Draw(sprite);
}
