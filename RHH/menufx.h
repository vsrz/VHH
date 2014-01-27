#pragma once

namespace MenuFX
{
	enum Effect{CHANGE, SELECT, DESELECT, BACK, BATTLESTART};

	void Initialize();
	void PlaySfx(Effect effect);
}