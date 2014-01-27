#include "WindowManager.h"
#include "StateManager.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "config.h"

static sf::RenderWindow window;
static unsigned int WindowHeight = Config::Default().GetInt("window_height");
static unsigned int WindowWidth = Config::Default().GetInt("window_width");
static bool fullscreen = Config::Default().GetBool("fullscreen");
static sf::Clock frametimer;
static sf::Uint32 lastframe = 0;

void WindowManager::Initialize()
{
	if(fullscreen)
	{
		window.create(sf::VideoMode(WindowWidth, WindowHeight), "Ragnarök Happy Hour", sf::Style::Fullscreen);
	}
	else
	{
		window.create(sf::VideoMode(WindowWidth, WindowHeight), "Ragnarök Happy Hour", sf::Style::Titlebar | sf::Style::Close);
	}

	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);
}

void WindowManager::Finalize()
{
	window.close();
}

void WindowManager::Draw(const std::vector<sf::Drawable*>& drawables)
{
	for(std::size_t i = 0; i < drawables.size(); ++i)
	{
		window.draw(*drawables[i]);
	}
}

void WindowManager::Draw(const sf::Drawable& drawable)
{
	window.draw(drawable);
}

void WindowManager::Begin()
{
	window.clear();
}

void WindowManager::End()
{
	window.display();
}

void WindowManager::Update()
{
	sf::Event event_handler;
	while(window.pollEvent(event_handler))
	{
		switch(event_handler.type)
		{
		case sf::Event::Closed:
			StateManager::Quit();
			break;
		}
	}
	lastframe = frametimer.getElapsedTime().asMilliseconds();
	frametimer.restart();
}

const sf::Vector2f& WindowManager::GetSize()
{
	return window.getView().getSize();
}

sf::Uint32 WindowManager::GetFrameTime()
{
	return lastframe;
}
