#include "statecharacterselect.h"
#include "StateManager.h"
#include "WindowManager.h"
#include "StateGame.h"
#include "Player.h"
#include "gamepad.h"
#include "music.h"
#include "menufx.h"
#include <SFML\Window\Joystick.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <vector>
#include "RoundCounter.h"

static sf::Texture background_tex;
static sf::Sprite background;

static sf::Texture background_activated_tex;
static sf::Sprite activated[4];

void StateCharacterSelect::Initialize()
{
	background_tex.loadFromFile("./Resources/Images/character_select_bg.png");
	background.setTexture(background_tex);

	background_activated_tex.loadFromFile("./Resources/Images/character_select_bg_selected.png");
	for(int i=0; i<4; i++)
		activated[i].setTexture(background_activated_tex);
	
	activated[0].setTextureRect(sf::IntRect(0, 0, 160, 480));
	activated[0].setPosition(0, 0);
	activated[1].setTextureRect(sf::IntRect(160, 0, 160, 480));
	activated[1].setPosition(160, 0);
	activated[2].setTextureRect(sf::IntRect(320, 0, 160, 480));
	activated[2].setPosition(320, 0);
	activated[3].setTextureRect(sf::IntRect(480, 0, 160, 480));
	activated[3].setPosition(480, 0);
}

StateCharacterSelect::StateCharacterSelect(unsigned int player_one)
{
	players[0].id = player_one;
	players[0].pos = 0;

	for(int i=0; i<4; i++)
	{
		players[i].has_chosen = false;
		players[i].toggle = false;
		colors_chosen[i] = false;
	}

	player_count = 1;

	button_tex.loadFromFile("./Resources/Images/player_buttons.png");
	for(int i=0; i<4; i++)
	{
		buttons_active[i].setTexture(button_tex);
		buttons_active[i].setTextureRect(sf::IntRect(32 * i, 0, 32, 32));
		buttons_done[i].setTexture(button_tex);
		buttons_done[i].setTextureRect(sf::IntRect(32 * i, 32, 32, 32));
	}

	buttons_active[0].setPosition(10.0f, 50.0f);
	buttons_active[1].setPosition(109.0f, 50.0f);
	buttons_active[2].setPosition(32.0f, 320.0f);
	buttons_active[3].setPosition(131.0f, 320.0f);
}

void StateCharacterSelect::Update()
{
	// Back
	for(unsigned int i=0; i<player_count; i++)
	{
		if(Gamepad::isButtonPressed(players[i].id, Gamepad::BUTTON_BACK))
		{
			MenuFX::PlaySfx(MenuFX::BACK);
			StateManager::Pop();
			return;
		}
	}

	// Player joining
	for(unsigned int i=0; i < sf::Joystick::Count; i++)
	{
		if(Gamepad::isButtonPressed(i, Gamepad::BUTTON_START))
		{
			bool taken = false;
			for(unsigned int j=0; j<player_count; j++)
				if(i == players[j].id)
					taken = true;

			if(!taken)
			{
				players[player_count].pos = player_count;
				players[player_count].id = i;
				player_count++;
			}
		}
	}

	// Choose character
	for(unsigned int i = 0; i<player_count; i++)
	{
		if(!players[i].has_chosen)
		{
			if(Gamepad::isButtonPressed(players[i].id, Gamepad::BUTTON_A) && colors_chosen[players[i].pos] == false)
			{
				players[i].has_chosen = true;
				colors_chosen[players[i].pos] = true;
				MenuFX::PlaySfx(MenuFX::SELECT);
				buttons_done[i].setPosition(buttons_active[i].getPosition());
				continue;
			}

			if(sf::Joystick::getAxisPosition(players[i].id, sf::Joystick::X) > 50 && !players[i].toggle)
			{
				players[i].pos++;
				players[i].pos %= 4;
				players[i].toggle = true;
				MenuFX::PlaySfx(MenuFX::CHANGE);
			}
			else if(sf::Joystick::getAxisPosition(players[i].id, sf::Joystick::X) < -50 && !players[i].toggle)
			{
				players[i].pos = players[i].pos == 0 ? 3 : players[i].pos - 1;
				players[i].toggle = true;
				MenuFX::PlaySfx(MenuFX::CHANGE);
			}
			else if(sf::Joystick::getAxisPosition(players[i].id, sf::Joystick::X) > -50 && sf::Joystick::getAxisPosition(players[i].id, sf::Joystick::X) < 50)
				players[i].toggle = false;
		}
		else if(Gamepad::isButtonPressed(players[i].id, Gamepad::BUTTON_B))
		{
			players[i].has_chosen = false;
			colors_chosen[players[i].pos] = false;
			MenuFX::PlaySfx(MenuFX::DESELECT);
		}
	}

	// Start
	bool want_start = false;
	bool can_start = true;
	for(unsigned int i=0; i<player_count && can_start; i++)
	{
		if(!players[i].has_chosen)
			can_start = false;
		if(sf::Joystick::isButtonPressed(players[i].id, 7))
			want_start = true;
	}

	if(can_start && want_start && player_count > 1)
	{
		std::vector<Player*> my_players;
		for(unsigned int i=0; i<player_count; i++)
			my_players.push_back(new Player(players[i].id, static_cast<Player::Color>(players[i].pos), 0, 0));

		MenuFX::PlaySfx(MenuFX::BATTLESTART);
		Music::Play(Music::BATTLE);
		RoundCounter::Reset();
		StateManager::Change(new StateGame(my_players));
		return;
	}

	if(player_count > 0)
		buttons_active[0].setPosition(10.0f + 155.0f * players[0].pos, 50.0f);
	if(player_count > 1)
		buttons_active[1].setPosition(109.0f + 155.0f * players[1].pos, 50.0f);
	if(player_count > 2)
		buttons_active[2].setPosition(32.0f + 155.0f * players[2].pos, 320.0f);
	if(player_count > 3)
		buttons_active[3].setPosition(131.0f + 155.0f * players[3].pos, 320.0f);
}

void StateCharacterSelect::Draw() const
{
	WindowManager::Draw(background);

	for(int i=0; i<4; i++)
		if(colors_chosen[i])
			WindowManager::Draw(activated[i]);

	for(unsigned int i=0; i<player_count; i++)
	{
		if(players[i].has_chosen)
			WindowManager::Draw(buttons_done[i]);
		else
			WindowManager::Draw(buttons_active[i]);
	}
}