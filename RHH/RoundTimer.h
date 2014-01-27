#pragma once

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class RoundTimer
{
public:
	RoundTimer(int round_time);
	void Draw() const;
	void Update();
	bool IsDone() const;
private:
	void UpdateTimerGraphicsPosition();
	sf::Text time_left_graphics;
	int prev_frame_time;
	int timer;
	sf::Font font;
};

