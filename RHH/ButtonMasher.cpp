#include "ButtonMasher.h"
#include "WindowManager.h"
#include <SFML/Window/Joystick.hpp>
#include "SoundFX.h"
#include "Player.h"
#include "WindowManager.h"
#include <SFML/Graphics/Texture.hpp>
#include "gamepad.h"

static sf::Texture drinking_tex[4];
static sf::Sprite drinking_sprt[4];
static sf::Sprite undrinking_sprt[4];

void ButtonMasher::Initialize()
{
	drinking_tex[0].loadFromFile("./Resources/Images/BarChars/red_drink.png");
	drinking_tex[1].loadFromFile("./Resources/Images/BarChars/blue_drink.png");
	drinking_tex[2].loadFromFile("./Resources/Images/BarChars/white_drink.png");
	drinking_tex[3].loadFromFile("./Resources/Images/BarChars/orange_drink.png");

	for(int i=0; i<4; i++)
	{
		drinking_sprt[i].setTexture(drinking_tex[i]);
		undrinking_sprt[i].setTexture(drinking_tex[i]);

		drinking_sprt[i].setTextureRect(sf::IntRect(drinking_tex[i].getSize().x / 2, 0, drinking_tex[i].getSize().x /2, 480));
		undrinking_sprt[i].setTextureRect(sf::IntRect(0, 0, drinking_tex[i].getSize().x/2, 480));
	}

	drinking_sprt[0].setPosition(5, 0);
	undrinking_sprt[0].setPosition(5, 0);

	drinking_sprt[1].setPosition(175, 0);
	undrinking_sprt[1].setPosition(175, 0);

	drinking_sprt[2].setPosition(305, 0);
	undrinking_sprt[2].setPosition(305, 0);

	drinking_sprt[3].setPosition(485, 0);
	undrinking_sprt[3].setPosition(485, 0);
}

ButtonMasher::ButtonMasher(Player* player):
mashes(0),
mashes_per_point(10),
player(player)
{
	//float fifth_size_x = WindowManager::GetSize().x * 0.20f * player->GetJoystickNo();
	//float size_y = WindowManager::GetSize().y;
	current_sprite = undrinking_sprt[player->GetColor()];
}

void ButtonMasher::Update()
{
	if(Gamepad::isButtonPressed(player->GetJoystickNo(),Gamepad::BUTTON_A))
		++mashes;

	if(mashes >= mashes_per_point)
	{
		SoundFX::PlaySfx(SoundFX::BURP);
		mashes = 0;
		player->AwardPoint();
	}

	if(Gamepad::IsButtonDown(player->GetJoystickNo(), Gamepad::BUTTON_A))
		current_sprite = drinking_sprt[player->GetColor()];
	else
		current_sprite = undrinking_sprt[player->GetColor()];
}

void ButtonMasher::Draw()
{
	WindowManager::Draw(current_sprite);
}
