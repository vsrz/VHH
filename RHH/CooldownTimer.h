#pragma once
class CooldownTimer
{
public:
	CooldownTimer(int max_frames);

	void Update();
	bool Fire();
private:
	int max_frames;
	int cur_frame;
};

