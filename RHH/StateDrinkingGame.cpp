#include "StateDrinkingGame.h"
#include "WindowManager.h"
#include "ButtonMasher.h"
#include "StateManager.h"
#include "StateGame.h"
#include "Player.h"
#include "StateManager.h"
#include "stategamemenu.h"
#include "gamepad.h"
#include "config.h"
#include "statescore.h"
#include "scoring.h"
#include <SFML\Graphics.hpp>
#include "RoundCounter.h"

static sf::Texture mash_tex;
static sf::Sprite mash_sprt[2];
static int mash_counter;
static bool mash_toggle;

void StateDrinkingGame::Initialize()
{
	mash_tex.loadFromFile("./Resources/Images/mash.png");
	mash_sprt[0].setTexture(mash_tex);
	mash_sprt[1].setTexture(mash_tex);
	mash_sprt[0].setTextureRect(sf::IntRect(0, 0, 178, 45));
	mash_sprt[1].setTextureRect(sf::IntRect(178, 0, 178, 45));
	mash_sprt[0].setPosition(320-89, 60);
	mash_sprt[1].setPosition(320-89, 60);

	ButtonMasher::Initialize();
}

StateDrinkingGame::StateDrinkingGame(std::vector<Player*> players):
players(players),
timer(Config::Default().GetInt("drinking_time"))
{
	RoundCounter::Increment();
	mash_counter = 0;
	mash_toggle = true;

	background_texture.loadFromFile("./Resources/Images/bar_bg.png");
	background_sprite.setTexture(background_texture);

	for(size_t i = 0; i < players.size(); ++i)
	{
		mashers.push_back(new ButtonMasher(players[i]));
	}
}

void StateDrinkingGame::Update()
{
	for(unsigned int i=0; i<players.size(); i++)
	{
		if(Gamepad::isButtonPressed(players[i]->GetJoystickNo(), Gamepad::BUTTON_START))
		{
			StateManager::Push(new StateGameMenu(this, players[i]->GetJoystickNo()));
			return;
		}
	}

	for(size_t i = 0; i < mashers.size(); ++i)
	{
		mashers[i]->Update();
	}

	timer.Update();

	if(timer.IsDone())
	{
		if(RoundCounter::IsDone())
			StateManager::Change(new StateScore(NULL, players, FINAL));
		else
			StateManager::Change(new StateScore(new StateGame(players), players, TOTAL));
	}

	mash_counter++;
	if(mash_counter > 12)
	{
		mash_toggle = !mash_toggle;
		mash_counter = 0;
	}
}

void StateDrinkingGame::Draw() const
{
	WindowManager::Draw(background_sprite);
	
	for(size_t i = 0; i < mashers.size(); ++i)
	{
		mashers[i]->Draw();
	}

	for(unsigned int i=0; i<players.size(); i++)
		Scoring::Draw(i, players[i]->GetScore());

	if(mash_toggle)
		WindowManager::Draw(mash_sprt[0]);
	else
		WindowManager::Draw(mash_sprt[1]);

	timer.Draw();
}

