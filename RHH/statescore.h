#pragma once

#include "State.h"
#include <vector>
class Player;

enum ScoreType{DEFAULT, TOTAL, FINAL};

class StateScore : public State
{
public:
	static void Initialize();
	StateScore(State* state, std::vector<Player*> players, ScoreType type = DEFAULT);
	void Update();
	void Draw() const;
private:
	State* state;
	unsigned int player_one;
	int counter;
	int num_players;
	ScoreType type;
};