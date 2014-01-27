#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <stack>

#include "Animation.h"
class AnimationController
{
public:
	enum Type { WALK, IDLE, ATTACK, STUCK, HIT };
	enum Color { RED, BLUE, WHITE, ORANGE };
	enum Direction { NORTH, SOUTH, WEST, EAST };

	AnimationController(Color color);
	~AnimationController();
	void Draw(float x, float y);
	void Update();	 

	Direction GetDirection() const { return direction; }
	void RemoveAnimation(Type type);
	void ChangeAnimation(Type type);
	void PushAnimation(Type type);
	void SetDirection(Direction direction);

private:
	Direction direction;

	sf::Texture walk_sheet;
	sf::Texture idle_sheet;
	sf::Texture attack_sheet;
	sf::Texture stuck_sheet;
	sf::Texture hit_sheet;
	
	std::stack<Animation*> animation_stack;
	Animation* walk_animation;
	Animation* idle_animation;
	Animation* attack_animation;
	Animation* stuck_animation;
	Animation* hit_animation;
};

