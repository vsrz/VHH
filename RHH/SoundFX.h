#pragma once

namespace SoundFX
{
	enum Effect{ ATTACK, HIT, MISS, BURP };

	void Initialize();
	void PlaySfx(Effect effect);
}