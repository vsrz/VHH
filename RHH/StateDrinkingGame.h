#pragma once

#include "State.h"
#include <vector>
#include "RoundTimer.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class ButtonMasher;
class Player;
class StateDrinkingGame : public State
{
public:
	static void Initialize();
	StateDrinkingGame(std::vector<Player*> players);
	StateDrinkingGame& operator=(const StateDrinkingGame&);

	void Update();
	void Draw() const;

private:
	std::vector<Player*> players;
	std::vector<ButtonMasher*> mashers;
	sf::Texture background_texture;
	sf::Sprite background_sprite;

	RoundTimer timer;
};

