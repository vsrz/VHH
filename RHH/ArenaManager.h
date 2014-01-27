#pragma once

namespace Collision { class Circle; }
namespace ArenaManager
{
	void Initialize();
	void ClampInside(Collision::Circle& box);
	void Draw();
};

