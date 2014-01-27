#include "Axe.h"
#include "Player.h"
#include "ProjectileManager.h"
#include "Projectile.h"
#include "axisalignedbox.h"
#include "SoundFX.h"

Axe::Axe() : 
cooldownTimer(100)
{}

void Axe::Update()
{
	cooldownTimer.Update();
}

void Axe::Fire(Player* player)
{
	if(cooldownTimer.Fire())
	{
		player->RunAttackAnimation();
		
		ProjectileManager::Push(new Projectile(player, 10, 0, sf::Vector2f(0,0)));

		SoundFX::PlaySfx(SoundFX::ATTACK);
	}
}

