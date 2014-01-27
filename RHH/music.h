#pragma once

namespace Music
{
	enum Setting{MENU, BATTLE};

	void Initialize();
	void Play(Setting setting);
}