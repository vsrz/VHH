#pragma once

class State
{
public:
	virtual ~State() {}

	virtual void Update() = 0;
	virtual void Draw() const = 0;
};

