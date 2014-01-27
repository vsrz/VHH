#pragma once

#include "circle.h"
#include "AnimationController.h"
#include <SFML/Graphics/Text.hpp>

class Gear;
class Player
{
public:
	enum Color { RED, BLUE, WHITE, ORANGE };

	Player(unsigned int joystick_no, Color color, float x, float y);
	~Player();

	void Update();
	void Draw();
	int GetFacing() const { return animationController.GetDirection(); }
	void RunAttackAnimation();
	void Hit(float x, float y);
	void AwardPoint();
	void Punish();
	void RemoveAttackAnimation();
	void HandleCollision(const std::vector<Player*>& players);
	void SetPosition(float x, float y) { collision_circle.SetPositionX(x); collision_circle.SetPositionY(y); }

	int GetScore()
	{ return points; }

	Color GetColor()
	{ return color; }

	const Collision::Circle& GetCollisionCircle() const { return collision_circle; }

	unsigned int GetJoystickNo() const { return joystick_no; }
private:
	Gear* main_hand;
	Gear* off_hand;
	int points;

	int freeze_frames;

	float propell_x;
	float propell_y;
	Collision::Circle collision_circle;

	sf::Text points_graphics;
	AnimationController animationController;

	unsigned int joystick_no;
	Color color;
};

