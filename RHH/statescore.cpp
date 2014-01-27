#include "statescore.h"
#include <SFML\Graphics.hpp>
#include "StateManager.h"
#include "WindowManager.h"
#include "gamepad.h"
#include "Player.h"
#include "music.h"
#include <sstream>

static sf::Font score_font;

static sf::Texture score_tex;
static sf::Sprite score_sprt;

static sf::Texture total_score_tex;
static sf::Sprite total_score_sprt;

static sf::Texture final_score_tex;
static sf::Sprite final_score_sprt;

static sf::Text scores[4];

static sf::Texture buttons_tex;
static sf::Sprite buttons[4];

void StateScore::Initialize()
{
	score_font.loadFromFile("./Resources/Fonts/tahoma.ttf");
	buttons_tex.loadFromFile("./Resources/Images/player_buttons.png");
	for(int i=0; i<4; i++)
	{
		buttons[i].setTexture(buttons_tex);
		buttons[i].setTextureRect(sf::IntRect(i*32, 0, 32, 32));
	}

	score_tex.loadFromFile("./Resources/Images/default_score.png");
	score_sprt.setTexture(score_tex);
	score_sprt.setPosition(180, 142);

	total_score_tex.loadFromFile("./Resources/Images/total_score.png");
	total_score_sprt.setTexture(total_score_tex);
	total_score_sprt.setPosition(180, 142);

	final_score_tex.loadFromFile("./Resources/Images/final_score.png");
	final_score_sprt.setTexture(final_score_tex);
	final_score_sprt.setPosition(180, 142);
}

StateScore::StateScore(State* state, std::vector<Player*> players, ScoreType type) :
state(state), player_one(players[0]->GetJoystickNo()), counter(0), type(type)
{
	num_players = players.size();
	for(int i = 0; i < num_players; i++)
	{
		std::stringstream temp;
		temp<<players[i]->GetScore();
		scores[i].setString(temp.str());
		scores[i].setColor(sf::Color(112, 69, 54));
	}

	for(unsigned int i=0; i<players.size(); i++)
	{
		switch(players[i]->GetColor())
		{
		case Player::RED:
			scores[i].setPosition(270, 200);
			buttons[i].setPosition(270-64, 200-16);
			break;
		case Player::BLUE:
			scores[i].setPosition(390, 200);
			buttons[i].setPosition(390-64, 200-16);
			break;
		case Player::WHITE:
			scores[i].setPosition(270, 270);
			buttons[i].setPosition(270-64, 270-16);
			break;
		case Player::ORANGE:
			scores[i].setPosition(390, 270);
			buttons[i].setPosition(390-64, 270-16);
			break;
		}
	}
}

void StateScore::Update()
{
	if(Gamepad::isButtonPressed(player_one, Gamepad::BUTTON_START))
	{
		if(type == FINAL)
		{
			Music::Play(Music::MENU);
			StateManager::Pop();
		}
		else
			StateManager::Change(state);
	}
}

void StateScore::Draw() const
{
	if(state)
		state->Draw();

	if(type == DEFAULT)
		WindowManager::Draw(score_sprt);
	else if(type == TOTAL)
		WindowManager::Draw(total_score_sprt);
	else if(type == FINAL)
		WindowManager::Draw(final_score_sprt);

	for(int i=0; i<num_players; i++)
	{
		WindowManager::Draw(scores[i]);
		WindowManager::Draw(buttons[i]);
	}
}