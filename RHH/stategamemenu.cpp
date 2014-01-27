#include "stategamemenu.h"
#include "WindowManager.h"
#include "StateManager.h"
#include "gamepad.h"
#include "music.h"
#include "menufx.h"
#include <SFML\Graphics.hpp>
#include <SFML\Window\Joystick.hpp>

static sf::Texture menu_tex;
static sf::Sprite menu_sprt;

static sf::Texture menu_pointer_tex;
static sf::Sprite menu_pointer_sprt;

StateGameMenu::StateGameMenu(State* state, unsigned int id) :
background_state(state), id(id), toggle(true)
{ menu_pointer_sprt.setPosition(208, 178); }

void StateGameMenu::Initialize()
{
	menu_pointer_tex.loadFromFile("./Resources/Images/gamemenu_pointer.png");
	menu_pointer_sprt.setTexture(menu_pointer_tex);

	menu_tex.loadFromFile("./Resources/Images/gamemenu.png");
	menu_sprt.setTexture(menu_tex);
	menu_sprt.setPosition(180, 142);
}

void StateGameMenu::Update()
{
	if(Gamepad::isButtonPressed(id, Gamepad::BUTTON_A))
	{
		if(toggle)
		{
			MenuFX::PlaySfx(MenuFX::SELECT);
			StateManager::Pop();
		}
		else
		{
			MenuFX::PlaySfx(MenuFX::BACK);
			Music::Play(Music::MENU);
			StateManager::Pop();
			StateManager::Pop();
		}
		return;
	}

	if(sf::Joystick::getAxisPosition(id,sf::Joystick::Y) < -50 && !toggle)
	{
		MenuFX::PlaySfx(MenuFX::CHANGE);
		toggle = true;
		menu_pointer_sprt.setPosition(208, 178);
	}
	else if(sf::Joystick::getAxisPosition(id,sf::Joystick::Y) > 50 && toggle)
	{
		MenuFX::PlaySfx(MenuFX::CHANGE);
		toggle = false;
		menu_pointer_sprt.setPosition(225, 203);
	}
}

void StateGameMenu::Draw() const
{
	background_state->Draw();
	WindowManager::Draw(menu_sprt);
	WindowManager::Draw(menu_pointer_sprt);
}