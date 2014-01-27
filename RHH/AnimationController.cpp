#include "AnimationController.h"
#include <cassert>
#include "config.h"

static float walk_speed = Config::Default().GetFloat("walk_animation_speed");
static float attack_speed = Config::Default().GetFloat("attack_animation_speed");
static float stuck_speed = Config::Default().GetFloat("stuck_animation_speed");
static float hit_speed = Config::Default().GetFloat("hit_animation_speed");

AnimationController::AnimationController(Color color):
direction(NORTH)
{
	switch(color)
	{
	case RED:
		walk_sheet.loadFromFile("./Resources/Images/Sheets/walksheet_red.png");
		idle_sheet.loadFromFile("./Resources/Images/Sheets/idlesheet_red.png");
		attack_sheet.loadFromFile("./Resources/Images/Sheets/attacksheet_red.png");
		stuck_sheet.loadFromFile("./Resources/Images/Sheets/stucksheet_red.png");
		hit_sheet.loadFromFile("./Resources/Images/Sheets/hitsheet_red.png");
		break;
	case BLUE:
		walk_sheet.loadFromFile("./Resources/Images/Sheets/walksheet_blue.png");
		idle_sheet.loadFromFile("./Resources/Images/Sheets/idlesheet_blue.png");
		attack_sheet.loadFromFile("./Resources/Images/Sheets/attacksheet_blue.png");
		stuck_sheet.loadFromFile("./Resources/Images/Sheets/stucksheet_blue.png");
		hit_sheet.loadFromFile("./Resources/Images/Sheets/hitsheet_blue.png");
		break;
	case WHITE:
		walk_sheet.loadFromFile("./Resources/Images/Sheets/walksheet_white.png");
		idle_sheet.loadFromFile("./Resources/Images/Sheets/idlesheet_white.png");
		attack_sheet.loadFromFile("./Resources/Images/Sheets/attacksheet_white.png");
		stuck_sheet.loadFromFile("./Resources/Images/Sheets/stucksheet_white.png");
		hit_sheet.loadFromFile("./Resources/Images/Sheets/hitsheet_white.png");
		break;
	case ORANGE:
		walk_sheet.loadFromFile("./Resources/Images/Sheets/walksheet_orange.png");
		idle_sheet.loadFromFile("./Resources/Images/Sheets/idlesheet_orange.png");
		attack_sheet.loadFromFile("./Resources/Images/Sheets/attacksheet_orange.png");
		stuck_sheet.loadFromFile("./Resources/Images/Sheets/stucksheet_orange.png");
		hit_sheet.loadFromFile("./Resources/Images/Sheets/hitsheet_orange.png");
		break;
	default:
		assert(!"Failed to load texture");
	}
	
	
	walk_animation = new Animation(walk_sheet, 4, 0, 8, walk_speed);
	idle_animation = new Animation(idle_sheet, 4, 0, 1, 1);
	attack_animation = new Animation(attack_sheet, 4, 0, 6, attack_speed, false);
	stuck_animation = new Animation(stuck_sheet, 4, 0, 6, stuck_speed, false);
	hit_animation = new Animation(hit_sheet, 4, 0, 1, hit_speed, false);

	animation_stack.push(walk_animation);
}

AnimationController::~AnimationController()
{
	delete walk_animation;
	delete idle_animation;
	delete attack_animation;
	delete stuck_animation;
}

void AnimationController::ChangeAnimation(Type type)
{
	if((type == IDLE || type == WALK) && animation_stack.size() > 1)
		return;

	if(!animation_stack.empty())
		animation_stack.pop();

	switch(type)
	{
	case WALK:
		animation_stack.push(walk_animation);
		break;
		
	case IDLE:
		animation_stack.push(idle_animation);
		break;
	
	default:
		assert(!"Animationfailure");
		break;
	}

	animation_stack.top()->SetRow(int(direction));
}

// for use with limited time (non-repeating) animations like attack
void AnimationController::PushAnimation(Type type)
{
	switch(type)
	{
	case ATTACK:
		attack_animation->Reset();
		animation_stack.push(attack_animation);
		break;
	case STUCK:
		RemoveAnimation(ATTACK);
		stuck_animation->Reset();
		animation_stack.push(stuck_animation);
		break;
	case HIT:
		RemoveAnimation(HIT);
		RemoveAnimation(ATTACK);
		hit_animation->Reset();
		animation_stack.push(hit_animation);
		break;
	}

	animation_stack.top()->SetRow(int(direction));
}

void AnimationController::SetDirection(Direction direction)
{
	this->direction = direction;
	animation_stack.top()->SetRow(int(direction));
}

void AnimationController::Draw(float x, float y)
{
	animation_stack.top()->Draw(x, y);
}

void AnimationController::RemoveAnimation(Type type)
{
	switch(type)
	{
	case ATTACK:
		if(animation_stack.top() == attack_animation)
			animation_stack.pop();
		break;
	}
}

void AnimationController::Update()
{
	if(animation_stack.empty())
	{
		animation_stack.push(walk_animation);
		animation_stack.top()->SetRow(int(direction));
	}

	if(animation_stack.top()->IsDone())
	{
		animation_stack.pop();
		animation_stack.top()->SetRow(int(direction));
	}

	animation_stack.top()->Update();
}
