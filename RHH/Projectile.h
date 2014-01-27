#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>
#include "circle.h"

class Player;
class Projectile
{
public:
	Projectile(Player* source, int start_frame, int life_time, const sf::Vector2f& velocity, bool miss_punish = true);
	void Update(const std::vector<Player*>& players);
	bool IsDone() const { return cur_frame - start_frame > life_time; }
	Player* GetSource() const { return source; }
	bool IsStarted() const { return cur_frame >= start_frame; }

private:
	Player* source;
	sf::Vector2f velocity;
	Collision::Circle* hitbox;
	int start_frame;
	int life_time;
	int cur_frame;
	bool miss_punish;
};

