#include "statemainmenu.h"
#include "WindowManager.h"
#include "StateManager.h"
#include "statecharacterselect.h"
#include "gamepad.h"
#include "menufx.h"
#include <SFML\Graphics.hpp>

static sf::Texture background;
static sf::Sprite bg_sprite;

static sf::Texture menu_tex;
static sf::Sprite menu_sprt;

static sf::Texture menuarrow_tex;
static sf::Sprite menuarrow_sprt;

static sf::Image white_out_img;
static sf::Texture white_out_tex;
static sf::Sprite white_out_sprt;

void StateMainMenu::Initialize()
{
	background.loadFromFile("./Resources/Images/mainmenubg.png");
	bg_sprite.setTexture(background);

	menuarrow_tex.loadFromFile("./Resources/Images/menuarrow.png");
	menuarrow_sprt.setTexture(menuarrow_tex);
	menuarrow_sprt.setPosition(235, 255);

	white_out_img.create(1, 1, sf::Color(255,255,255,0));
	white_out_tex.loadFromImage(white_out_img);
	white_out_sprt.setTexture(white_out_tex);
	white_out_sprt.setScale(640, 480);
	white_out_sprt.setColor(sf::Color(255,255,255,0));
}

void StateMainMenu::Update()
{

	if(Gamepad::isButtonPressed(player_one, Gamepad::BUTTON_BACK))
	{
		MenuFX::PlaySfx(MenuFX::BACK);
		StateManager::Pop();
		return;
	}
	if(Gamepad::isButtonPressed(player_one, Gamepad::BUTTON_A))
	{
		if(toggle)
		{
			MenuFX::PlaySfx(MenuFX::SELECT);
			StateManager::Push(new StateCharacterSelect(player_one));
		}
		else
			StateManager::Quit();
		return;
	}

	if(sf::Joystick::getAxisPosition(player_one, sf::Joystick::Y) < -50 && !toggle)
	{
		MenuFX::PlaySfx(MenuFX::CHANGE);
		toggle = true;
		menuarrow_sprt.setPosition(235, 255);
	}
	else if(sf::Joystick::getAxisPosition(player_one, sf::Joystick::Y) > 50 && toggle)
	{
		MenuFX::PlaySfx(MenuFX::CHANGE);
		toggle = false;
		menuarrow_sprt.setPosition(235, 310);
	}

	if(counter > 0)
	{
		const int STEP = 16;
		counter = counter-STEP >= 0 ? counter-STEP : 0;
		white_out_sprt.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(counter)));
	}
	
}

void StateMainMenu::Draw() const
{
	WindowManager::Draw(bg_sprite);
	WindowManager::Draw(menuarrow_sprt);
	WindowManager::Draw(white_out_sprt);
}