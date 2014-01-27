#include "ProjectileManager.h"
#include <vector>
#include "Player.h"
#include "Projectile.h"

typedef std::vector<Projectile*> ProjVec;
static ProjVec projectiles;

void ProjectileManager::Push(Projectile* projectile)
{
	projectiles.push_back(projectile);
}

void ProjectileManager::Update(const std::vector<Player*>& players)
{
	for(ProjVec::iterator proj = projectiles.begin(); proj != projectiles.end();)
	{
		(*proj)->Update(players);

		if((*proj)->IsDone())
		{
			delete *proj;
			proj = projectiles.erase(proj);
		} else
		{
			++proj;
		}
	}
}

void ProjectileManager::PurgeUnstartedForPlayer(Player* player)
{
	for(ProjVec::iterator proj = projectiles.begin(); proj != projectiles.end();)
	{
		if((*proj)->GetSource() == player && !(*proj)->IsStarted())
		{
			player->RemoveAttackAnimation();
			proj = projectiles.erase(proj);
		}
		else
		{
			++proj;
		}
	}
}
