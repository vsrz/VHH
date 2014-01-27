#include "music.h"
#include <SFML\Audio.hpp>

static sf::Music menu_snd;
static sf::Music battle_snd;

void Music::Initialize()
{
	menu_snd.openFromFile("./Resources/Sounds/menumusic.ogg");
	menu_snd.setVolume(60.0f);
	menu_snd.setLoop(true);
	battle_snd.openFromFile("./Resources/Sounds/battlemusic.ogg");
	battle_snd.setVolume(40.0f);
	battle_snd.setLoop(true);

	menu_snd.play();
}

void Music::Play(Music::Setting setting)
{
	switch(setting)
	{
	case MENU:
		menu_snd.play();
		battle_snd.stop();
		break;
	case BATTLE:
		menu_snd.stop();
		battle_snd.play();
		break;
	}
}