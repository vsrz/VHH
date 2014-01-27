#include "SoundFX.h"
#include <SFML/Audio.hpp>
#include <random>
#include <iostream>

static sf::SoundBuffer attack1_snd;
static sf::SoundBuffer attack2_snd;
static sf::SoundBuffer attack3_snd;
static sf::Sound attack_sounds[3];

static sf::SoundBuffer hit1_snd;
static sf::SoundBuffer hit2_snd;
static sf::Sound hit_sounds[2];

static sf::SoundBuffer miss1_snd;
static sf::SoundBuffer miss2_snd;
static sf::Sound miss_sounds[2];

static sf::SoundBuffer burp1_snd;
static sf::SoundBuffer burp2_snd;
static sf::SoundBuffer burp3_snd;
static sf::Sound burp_sounds[3];

void SoundFX::Initialize()
{
	attack1_snd.loadFromFile("./Resources/Sounds/Battle/Player_attack1.wav");
	attack_sounds[0].setBuffer(attack1_snd);
	attack2_snd.loadFromFile("./Resources/Sounds/Battle/Player_attack2.wav");
	attack_sounds[1].setBuffer(attack2_snd);
	attack3_snd.loadFromFile("./Resources/Sounds/Battle/Player_attack3.wav");
	attack_sounds[2].setBuffer(attack3_snd);

	hit1_snd.loadFromFile("./Resources/Sounds/Battle/Player_hit1.wav");
	hit_sounds[0].setBuffer(hit1_snd);
	hit2_snd.loadFromFile("./Resources/Sounds/Battle/Player_hit2.wav");
	hit_sounds[1].setBuffer(hit2_snd);

	miss1_snd.loadFromFile("./Resources/Sounds/Battle/Player_miss1.wav");
	hit_sounds[0].setBuffer(miss1_snd);
	miss2_snd.loadFromFile("./Resources/Sounds/Battle/Player_miss2.wav");
	hit_sounds[1].setBuffer(miss2_snd);

	burp1_snd.loadFromFile("./Resources/Sounds/Battle/Player_burp1.wav");
	burp2_snd.loadFromFile("./Resources/Sounds/Battle/Player_burp2.wav");
	burp3_snd.loadFromFile("./Resources/Sounds/Battle/Player_burp3.wav");
	burp_sounds[0].setBuffer(burp1_snd);
	burp_sounds[1].setBuffer(burp2_snd);
	burp_sounds[2].setBuffer(burp3_snd);
}

void SoundFX::PlaySfx(Effect effect)
{
	srand(unsigned int(time(0)));
	int r = rand();

	switch(effect)
	{
	case ATTACK:
		attack_sounds[r%3].play();
		break;
	case HIT:
		hit_sounds[r%2].play();
		break;
	case MISS:
		miss_sounds[r%2].play();
		break;
	case BURP:
		if(burp_sounds[r%3].getStatus() == sf::SoundSource::Stopped)
			burp_sounds[r%3].play();
		break;
	}
}