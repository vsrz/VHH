#include "CooldownTimer.h"

CooldownTimer::CooldownTimer(int max_frames):
max_frames(max_frames),
cur_frame(0)
{
}

void CooldownTimer::Update()
{
	if(cur_frame < max_frames)
	{
		++cur_frame;
	}
}

bool CooldownTimer::Fire()
{
	if(cur_frame >= max_frames)
	{
		cur_frame = 0;
		return true;
	}
	
	return false;
}
