#pragma once

#include "Gear.h"
#include "CooldownTimer.h"

class Player;
class Axe : public Gear
{
public:
	Axe();

	void Update();
	void Fire(Player* player);
private:
	CooldownTimer cooldownTimer;
};

