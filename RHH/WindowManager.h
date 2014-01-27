#pragma once
#include <vector>

#include <SFML/System/Vector2.hpp>

namespace sf { class Drawable; }
namespace WindowManager
{
	void Initialize();
	void Finalize();

	void Draw(const std::vector<sf::Drawable*>& drawables);
	void Draw(const sf::Drawable& drawables);

	const sf::Vector2f& GetSize();
	unsigned int GetFrameTime();

	void Update();

	void Begin();
	void End();
};

