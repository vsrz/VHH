#include "Player.h"
#include <SFML/Window/Joystick.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "config.h"
#include "Gear.h"
#include <iostream>
#include "Axe.h"
#include "ArenaManager.h"
#include <SFML/Graphics/Font.hpp>
#include "WindowManager.h"
#include <sstream>
#include <cmath>
#include "ProjectileManager.h"
#include "SoundFX.h"

static float player_speed = Config::Default().GetFloat("player_speed") / 60.0f;
static float propell_force = Config::Default().GetFloat("propell_force");

template <typename T> int sgn(T val)
{ return (val > T(0)) - (val < T(0)); }

Player::Player(unsigned int joystick_no, Color color, float x, float y):
joystick_no(joystick_no),
main_hand(new Axe),
off_hand(0),
collision_circle(x, y, 16),
points(0),
propell_x(0),
propell_y(0),
freeze_frames(0),
animationController(AnimationController::Color(color)),
color(color)
{}

Player::~Player()
{
	delete main_hand;
	delete off_hand;
}

void Player::Update()
{
	if(freeze_frames <= 0)
	{
		float x_pos = sf::Joystick::getAxisPosition(joystick_no, sf::Joystick::X) / 100.0f;
		float y_pos = sf::Joystick::getAxisPosition(joystick_no, sf::Joystick::Y) / 100.0f;
	
		if((fabs(x_pos) > 0.3 || fabs(y_pos) > 0.3) || ((fabs(propell_x) > 0.01) || (fabs(propell_y) > 0.01)))
		{
			animationController.ChangeAnimation(AnimationController::WALK);

			float x = x_pos * player_speed;
			float y = y_pos * player_speed;
			
			// propell is for when the player is hit
			if(fabs(propell_x) > 0.01)
			{
				x = propell_x;

				propell_x *= 0.9f;
			}

			if(fabs(propell_y) > 0.01)
			{
				y = propell_y;

				propell_y *= 0.9f;
			}

			if(fabs(x) > fabs(y))
				animationController.SetDirection(x > 0 ? AnimationController::EAST : AnimationController::WEST);
			else
				animationController.SetDirection(y > 0 ? AnimationController::SOUTH : AnimationController::NORTH);

			collision_circle.Move(x,y);
			ArenaManager::ClampInside(collision_circle);
		}
		else
		{
			animationController.ChangeAnimation(AnimationController::IDLE);
		}
	}
	else
	{
		--freeze_frames;
	}
	
	
	if(main_hand)
	{
		main_hand->Update();

		if(sf::Joystick::isButtonPressed(joystick_no, 0))
		{
			main_hand->Fire(this);
		}
	}

	if(off_hand)
	{
		off_hand->Update();

		if(sf::Joystick::isButtonPressed(joystick_no, 3))
		{
			off_hand->Fire(this);
		}
	}

	animationController.Update();
}

void Player::HandleCollision(const std::vector<Player*>& players)
{
	for(size_t i = 0; i < players.size(); ++i)
	{
		if(players[i] == this)
			continue;

		Collision::Circle& collider = players[i]->collision_circle;

		if(collision_circle.Intersect(collider))
		{
			float vx = collider.GetPositionX() - collision_circle.GetPositionX();
			float vy = collider.GetPositionY() - collision_circle.GetPositionY();

			float vl = sqrt(vx*vx + vy*vy);

			float vxn = vx / vl;
			float vyn = vy / vl;

			float overlap = collider.GetRadius() + collision_circle.GetRadius() - vl;
			overlap /= 2;

			collider.Move(vxn * overlap, vyn * overlap);
			collision_circle.Move(-vxn * overlap, -vyn * overlap);

			ArenaManager::ClampInside(collider);
			ArenaManager::ClampInside(collision_circle);
		}
	}
}

void Player::AwardPoint()
{
	++points;

}

void Player::Punish()
{
	freeze_frames = 100;

	SoundFX::PlaySfx(SoundFX::MISS);
	animationController.PushAnimation(AnimationController::STUCK);
}

void Player::Hit(float x, float y)
{
	/*float dif_x = collision_box.GetPositionX() - x;
	float dif_y = collision_box.GetPositionY() - y;

	float length = dif_x * dif_x + dif_y * dif_y;
	if(length  != 0)
	{
		length = sqrt(length);
		propell_x = dif_x / length * propell_force;
		propell_y = dif_y / length * propell_force;
	}*/

	float dt_x = collision_circle.GetPositionX() - x;
	float dt_y = collision_circle.GetPositionY() - y;

	if(abs(dt_x) > abs(dt_y))
		propell_x = propell_force * sgn(dt_x);

	else
		propell_y = propell_force * sgn(dt_y);

	SoundFX::PlaySfx(SoundFX::HIT);
//	AnimationController::Direction dir = AnimationController::Direction(GetFacing());
	ProjectileManager::PurgeUnstartedForPlayer(this);
	animationController.PushAnimation(AnimationController::HIT);
	//animationController.setDirection(dir);
}

void Player::RemoveAttackAnimation()
{
	animationController.RemoveAnimation(AnimationController::ATTACK);
}

void Player::RunAttackAnimation()
{
	animationController.PushAnimation(AnimationController::ATTACK);
}

void Player::Draw()
{
	animationController.Draw(collision_circle.GetPositionX(), collision_circle.GetPositionY()-16);
}
