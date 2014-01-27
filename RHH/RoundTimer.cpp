#include "RoundTimer.h"
#include <sstream>
#include "WindowManager.h"
#include <iostream>

RoundTimer::RoundTimer(int round_time):
timer(round_time * 1000 + 999),
prev_frame_time(0)
{
	font.loadFromFile("./Resources/Fonts/jokerman.ttf");
	time_left_graphics.setFont(font);
	time_left_graphics.setCharacterSize(36);
	
	time_left_graphics.setString("0");

	UpdateTimerGraphicsPosition();
}

void RoundTimer::Update()
{
	timer -= WindowManager::GetFrameTime();
	sf::Color white(sf::Color::White);
	if(timer / 1000 <= 9)
	{
		time_left_graphics.setColor(white);
	}

	if(timer > prev_frame_time - 1000)
	{
		UpdateTimerGraphicsPosition();

		prev_frame_time = timer;
	}	
}

void RoundTimer::Draw() const
{
	WindowManager::Draw(time_left_graphics);
}

bool RoundTimer::IsDone() const
{
	return timer <= 1000;
}

void RoundTimer::UpdateTimerGraphicsPosition()
{
	std::stringstream timerStream;
	timerStream << timer / 1000;

	time_left_graphics.setString(timerStream.str());
	time_left_graphics.setPosition(WindowManager::GetSize().x / 2 - time_left_graphics.getGlobalBounds().width/2, 5);
}
