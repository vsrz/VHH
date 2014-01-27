#pragma once

#include <vector>

class Player;
class Projectile;
namespace ProjectileManager
{
	void Push(Projectile* projectile);
	void Update(const std::vector<Player*>& players);
	void PurgeUnstartedForPlayer(Player* player); // for removing a player who's strike / shot hasn't been sent away but is queued (i.e. animation is beginning but strike not delivered yet)
};
