#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"


class StateMainMenu : public State
{
public:
	StateMainMenu(unsigned int player_one) : player_one(player_one), toggle(true), counter(255) {}
	static void Initialize();

	void Update();
	void Draw() const;

private:
	unsigned int player_one;
	bool toggle;
	int counter;
};