#include "statestartscreen.h"
#include "WindowManager.h"
#include "StateManager.h"
#include "statemainmenu.h"
#include <SFML\Graphics.hpp>
#include <SFML\Window\Keyboard.hpp>
#include "gamepad.h"
#include <SFML\Audio.hpp>

static sf::Texture background;
static sf::Sprite bg_sprite;
static sf::Sound start;
static sf::SoundBuffer start_snd;

void StateStartScreen::Initialize()
{
	background.loadFromFile("./Resources/Images/startscreenbg.png");
	bg_sprite.setTexture(background);

	start_snd.loadFromFile("./Resources/Sounds/start.wav");
	start.setBuffer(start_snd);
	start.setVolume(30.0f);
}

void StateStartScreen::Update()
{	
	for(int i=0; i < sf::Joystick::Count; i++)
	{
		if(Gamepad::isButtonPressed(i, Gamepad::BUTTON_START))
		{
			StateManager::Push(new StateMainMenu(i));
			start.play();
			return;
		}
	}
}

void StateStartScreen::Draw() const
{
	WindowManager::Draw(bg_sprite);
}