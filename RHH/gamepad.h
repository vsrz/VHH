#pragma once

namespace Gamepad
{
	enum XboxButton
	{ 
		BUTTON_A, BUTTON_B, BUTTON_X, BUTTON_Y,
		BUTTON_LB, BUTTON_RB, BUTTON_BACK,
		BUTTON_START, BUTTON_COUNT
	};

	void Update();

	bool IsButtonDown(unsigned int id, XboxButton button);
	bool isButtonPressed(unsigned int id, XboxButton button);
	bool IsButtonReleased(unsigned int id, XboxButton button);
}