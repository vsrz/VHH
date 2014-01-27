#pragma once

#include "State.h"

class StateStartScreen : public State
{
public:
	static void Initialize();

	void Update();
	void Draw() const;

private:
};