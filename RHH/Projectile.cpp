#include "Projectile.h"
#include "Player.h"
#include <iostream>

Projectile::Projectile(Player* source, int start_frame, int life_time, const sf::Vector2f& velocity, bool miss_punish):
source(source),
velocity(velocity),
hitbox(0),
start_frame(start_frame),
life_time(life_time),
cur_frame(0),
miss_punish(miss_punish)
{

}

void Projectile::Update(const std::vector<Player*>& players)
{
	Player* best = players[0];
	for(unsigned int i = 0; i < players.size(); i++)
		if(players[i]->GetScore() > best->GetScore())
			best = players[i];

	if(cur_frame >= start_frame && cur_frame - start_frame <= life_time)
	{
		if(hitbox == 0)
		{
			hitbox = new Collision::Circle(source->GetCollisionCircle());

			switch(source->GetFacing())
			{
			case 0:
				hitbox->SetPositionY(hitbox->GetPositionY() + hitbox->GetRadius());
				hitbox->SetRadius(48);
				break;
			case 1:
				hitbox->SetPositionY(hitbox->GetPositionY() - hitbox->GetRadius());
				hitbox->SetRadius(48);
				break;
			case 2:
				hitbox->SetPositionX(hitbox->GetPositionX() + hitbox->GetRadius());
				hitbox->SetRadius(48);
				break;
			case 3:
				hitbox->SetPositionX(hitbox->GetPositionX() - hitbox->GetRadius());
				hitbox->SetRadius(48);
				break;
			}
		}

		for(size_t i = 0; i < players.size(); ++i)
		{
			if(players[i] != source && hitbox->Intersect(players[i]->GetCollisionCircle()))
			{
				players[i]->Hit(hitbox->GetPositionX(), hitbox->GetPositionY());
				source->AwardPoint();

				if(players[i] == best)
					source->AwardPoint();

				cur_frame = 999;
				return;
			}
		}

		if(miss_punish)
		{
			source->Punish();
			cur_frame = 999;
			return;
		}
		else
		{
			hitbox->Move(velocity.x, velocity.y);
		}
	}

	++cur_frame;
}
