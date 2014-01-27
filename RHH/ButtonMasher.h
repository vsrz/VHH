#pragma once


#include <SFML/Graphics/Sprite.hpp>

class Player;
class ButtonMasher
{
public:
	static void Initialize();

	ButtonMasher(Player* player);
	void Update();
	void Draw();
private:
	Player* player;
	int mashes;
	int mashes_per_point;
	sf::Sprite current_sprite;
};

