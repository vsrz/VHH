#include "StateManager.h"
#include "WindowManager.h"
#include "statestartscreen.h"
#include "statemainmenu.h"
#include "statecharacterselect.h"
#include "stategamemenu.h"
#include "stategame.h"
#include <SFML\Window.hpp>

#include "Player.h"
#include "StateGame.h"
#include "StateDrinkingGame.h"
#include "gamepad.h"
#include "music.h"
#include "menufx.h"
#include "scoring.h"
#include <vector>
#include "SoundFX.h"
#include "statescore.h"
#include "ButtonMasher.h"

int main()
{
	WindowManager::Initialize();
	
	StateStartScreen::Initialize();
	StateMainMenu::Initialize();
	StateCharacterSelect::Initialize();
	StateGameMenu::Initialize();
	StateDrinkingGame::Initialize();
	StateScore::Initialize();
	StateGame::Initialize();
	ButtonMasher::Initialize();
	Music::Initialize();
	MenuFX::Initialize();
	Scoring::Initialize();
	SoundFX::Initialize();

	StateManager::Push(new StateStartScreen());
	
	while(StateManager::IsRunning())
	{
		WindowManager::Update();
		Gamepad::Update();
		StateManager::Update();
		StateManager::Draw();
	}

	StateManager::Clear();
	WindowManager::Finalize();

	return 0;
}