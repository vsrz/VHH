#include "menufx.h"
#include <SFML\Audio.hpp>

static sf::Sound change;
static sf::SoundBuffer change_snd;

static sf::Sound select;
static sf::SoundBuffer select_snd;

static sf::Sound deselect;
static sf::SoundBuffer deselect_snd;

static sf::Sound back;
static sf::SoundBuffer back_snd;

static sf::Sound battle_start;
static sf::SoundBuffer battle_start_snd;

void MenuFX::Initialize()
{
	change_snd.loadFromFile("./Resources/Sounds/change_selection.wav");
	change.setBuffer(change_snd);
	//change.setVolume(30.0f);

	select_snd.loadFromFile("./Resources/Sounds/select.wav");
	select.setBuffer(select_snd);

	deselect_snd.loadFromFile("./Resources/Sounds/deselect.wav");
	deselect.setBuffer(deselect_snd);

	back_snd.loadFromFile("./Resources/Sounds/back.wav");
	back.setBuffer(back_snd);

	battle_start_snd.loadFromFile("./Resources/Sounds/battle_start.wav");
	battle_start.setBuffer(battle_start_snd);
	battle_start.setVolume(50.0f);
}

void MenuFX::PlaySfx(Effect effect)
{
	switch(effect)
	{
	case CHANGE:
		change.play();
		break;
	case SELECT:
		select.play();
		break;
	case DESELECT:
		deselect.play();
		break;
	case BACK:
		back.play();
		break;
	case BATTLESTART:
		battle_start.play();
		break;
	}
}