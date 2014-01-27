#pragma once

class Player;
class Gear
{
public:
	Gear() {}
	virtual ~Gear() {}
	virtual void Fire(Player* player) = 0;
	virtual void Update() = 0;
};

