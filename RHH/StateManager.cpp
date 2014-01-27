#include "StateManager.h"
#include "State.h"
#include "WindowManager.h"
#include <stack>

static std::stack<State*> states;
static bool run = true;
static bool state_changed = false;

bool StateManager::IsRunning()
{
	return !states.empty() && run;
}

void StateManager::Update()
{
	if(state_changed)
		state_changed = false;

	if(states.size() > 0)
		states.top()->Update();
}

void StateManager::Draw()
{
	if(states.size() > 0 && !state_changed)
	{
		WindowManager::Begin();
		states.top()->Draw();
		WindowManager::End();
	}
}

void StateManager::Change(State* state)
{
	if(states.size() > 0)
	{
		delete states.top();
		states.pop();
	}

	states.push(state);

	state_changed = true;
	//states.top().Resume();
}

void StateManager::Push(State* state)
{
	//states.top().Pause();
	states.push(state);

	state_changed = true;
	//states.top().Initialize();
	
}

void StateManager::Pop()
{
	// delete states.top();
	states.pop();
	//if(states.size() > 0)
	//	states.top().Resume();
}

void StateManager::Quit()
{ run = false; }

void StateManager::Clear()
{
	while(!states.empty())
	{ delete states.top(); states.pop(); }
}
