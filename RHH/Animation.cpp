#include "Animation.h"
#include "WindowManager.h"
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <cassert>

Animation::Animation(const sf::Texture& texture, unsigned int num_rows, unsigned int row, int num_frames, float speed, bool repeat) :
num_frames(num_frames),
sprite(texture),
num_rows(num_rows),
cur_frame(1),
row(row),
speed(1.0f / speed),
done(false),
repeat(repeat),
frame_timer(0)
{
	/*if(num_frames > 1)
	{*/
		sf::IntRect texRect(
			0, texture.getSize().x/num_rows * row,
			texture.getSize().x / num_frames, texture.getSize().y / num_rows
			);
		sprite.setTextureRect(texRect);

		sprite.setOrigin(texRect.width / 2.0f, texRect.height / 2.0f);
	/*}
	else
		sprite.setOrigin(texture.getWidth() / 2.0f, texture.getHeight() / 2.0f);*/
}

void Animation::Update()
{
	if(num_frames < 1)
		assert(!"An animation has less then 1 frame");

	frame_timer += 1.0f/60.0f;
	if(frame_timer >= speed)
	{
		++cur_frame;
		frame_timer -= speed;
	}
	if(cur_frame >= num_frames)
	{
		if(!repeat)
			done = true;

		cur_frame = 0;
	}


	/*if(frame_timer > 1.0f)
	{
		++cur_frame;
		frame_timer = 0;
	}
	else
	{
		frame_timer += speed;
	}

	if(cur_frame >= num_frames)
	{
		if(!repeat)
			done = true;

		cur_frame = 0;
	}*/

	int xSize = sprite.getTexture()->getSize().x / num_frames;
	int ySize = sprite.getTexture()->getSize().y / num_rows;

	sf::IntRect texRect
	(
		xSize * cur_frame,
		ySize * row,
		xSize,
		ySize
	);

	sprite.setTextureRect(texRect);
}

void Animation::Draw(float x, float y)
{
	sprite.setPosition(x,y);
	WindowManager::Draw(sprite);
}