#pragma once

#include "State.h"

class StateGameMenu :public State
{
public:
	StateGameMenu(State* state, unsigned int id);
	static void Initialize();

	void Update();
	void Draw() const;

private:
	State* background_state;
	unsigned int id;
	bool toggle;
};