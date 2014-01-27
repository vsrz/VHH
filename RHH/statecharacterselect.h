#pragma once

#include "State.h"
#include <SFML\Graphics.hpp>

class StateCharacterSelect : public State
{
public:
	static void Initialize();

	StateCharacterSelect(unsigned int player_one);

	void Update();
	void Draw() const;

private:
	struct{
		unsigned int id;
		unsigned int pos;
		bool toggle;
		bool has_chosen;
	}players[4];
	bool colors_chosen[4];
	unsigned int player_count;

	sf::Texture button_tex;
	sf::Sprite buttons_active[4];
	sf::Sprite buttons_done[4];
};