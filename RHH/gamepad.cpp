#include "gamepad.h"
#include <SFML\Window\Joystick.hpp>

static struct{
	bool down[sf::Joystick::ButtonCount];
	bool released[sf::Joystick::ButtonCount];
	bool pressed[sf::Joystick::ButtonCount];
}controllers[sf::Joystick::Count];

namespace Gamepad
{
	void Initialize()
	{
		for(int i=0; i<sf::Joystick::Count; i++)
		{
			for(int j=0; j < BUTTON_COUNT; j++)
			{
				controllers[i].pressed[j] = false;
				controllers[i].released[j] = false;
				controllers[i].down[j] = false;
			}
		}
	}

	void Update()
	{
		for(int i=0; i<sf::Joystick::Count; i++)
		{
			if(!sf::Joystick::isConnected(i))
				continue;

			for(int j=0; j < BUTTON_COUNT; j++)
			{
				controllers[i].pressed[j] = sf::Joystick::isButtonPressed(i, j) && !controllers[i].down[j];
				controllers[i].released[j] = !sf::Joystick::isButtonPressed(i, j) && controllers[i].down[j];
				controllers[i].down[j] = sf::Joystick::isButtonPressed(i, j);
			}
		}
	}

	bool IsButtonDown(unsigned int id, XboxButton button)
	{ return controllers[id].down[button]; }

	bool isButtonPressed(unsigned int id, XboxButton button)
	{ return controllers[id].pressed[button]; }

	bool IsButtonReleased(unsigned int id, XboxButton button)
	{ return controllers[id].released[button]; }
}