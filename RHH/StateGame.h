#pragma once

#include <vector>
#include "State.h"
#include "RoundTimer.h"

class Player;
class StateGame : public State
{
public:
	static void Initialize();
	StateGame(std::vector<Player*> players);

	virtual void Update();
	virtual void Draw() const;
private:
	std::vector<Player*> players;
	Player* best;
	RoundTimer timer;
};

