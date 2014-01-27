#pragma once

#include <SFML/Graphics/Sprite.hpp>

class Animation
{
public:
	Animation(const sf::Texture& texture, unsigned int num_rows, unsigned int row, int num_frames, float speed, bool repeat = true);

	void Update();
	void Draw(float x, float y);

	void Reset() { done = false; }
	bool IsDone() { return done; }
	
	int GetCurFrame() const { return cur_frame; }
	int GetNumFrames() const { return num_frames; }

	int GetRow() const { return row; }
	void SetRow(int row){ this->row = row; }	

private:
	sf::Sprite sprite;
	int num_frames;
	int cur_frame;
	int num_rows;
	int row;
	bool done;
	bool repeat;
	float frame_timer;
	float speed;
};

