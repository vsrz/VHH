#pragma once

class State;
namespace StateManager
{
	bool IsRunning();
	void Update();
	void Draw();

	void Change(State* state);
	void Push(State* state);
	void Pop();

	void Quit();
	void Clear();
}
