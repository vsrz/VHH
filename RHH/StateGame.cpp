#include "StateGame.h"
#include "Player.h"
#include "ArenaManager.h"
#include "StateDrinkingGame.h"
#include "StateManager.h"
#include "ProjectileManager.h"
#include <sstream>
#include "WindowManager.h"
#include "config.h"
#include "gamepad.h"
#include "stategamemenu.h"
#include "statescore.h"
#include "scoring.h"
#include "RoundCounter.h"
#include <SFML\Graphics.hpp>

static sf::Texture crown_tex;
static sf::Sprite crown;

void StateGame::Initialize()
{
	crown_tex.loadFromFile("./Resources/Images/crown.png");
	crown.setTexture(crown_tex);
	crown.setPosition(-100, -100);
}

StateGame::StateGame(std::vector<Player*> players):
players(players),
best(0),
timer(Config::Default().GetInt("fighting_time"))
{
	ArenaManager::Initialize();

	RoundCounter::Increment();

	if(players.size() > 0)
		players[0]->SetPosition(110,160);
	if(players.size() > 1)
		players[1]->SetPosition(540,160);
	if(players.size() > 2)
		players[2]->SetPosition(110,400);
	if(players.size() > 3)
		players[3]->SetPosition(540,400);
}

void StateGame::Update()
{
	for(unsigned int i=0; i<players.size(); i++)
	{
		if(Gamepad::isButtonPressed(players[i]->GetJoystickNo(), Gamepad::BUTTON_START))
		{
			StateManager::Push(new StateGameMenu(this, players[i]->GetJoystickNo()));
			return;
		}
	}

	ProjectileManager::Update(players);

	for(size_t i = 0; i < players.size(); ++i)
	{
		players[i]->Update();
		players[i]->HandleCollision(players);
	}
	
	timer.Update();

	if(timer.IsDone())
	{
		if(RoundCounter::IsDone())
			StateManager::Change(new StateScore(NULL, players, FINAL));
		else
			StateManager::Change(new StateScore(new StateDrinkingGame(players), players, TOTAL));

		return;
	}	

	if(!best)
		best = players.front();

	for(unsigned int i = 0; i < players.size(); i++)
		if(players[i]->GetScore() > best->GetScore())
			best = players[i];

	crown.setPosition(best->GetCollisionCircle().GetPositionX()-8, best->GetCollisionCircle().GetPositionY()-50);
}

void StateGame::Draw() const
{
	ArenaManager::Draw();

	for(size_t i = 0; i < players.size(); ++i)
	{
		players[i]->Draw();
	}

	WindowManager::Draw(crown);

	// NOTE: The joystick_no may not correspond to the player number

	for(unsigned int i=0; i<players.size(); i++)
		Scoring::Draw(i, players[i]->GetScore());

	timer.Draw();
}
