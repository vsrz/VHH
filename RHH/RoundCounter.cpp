#include "RoundCounter.h"
#include "config.h"

static int max_rounds = Config::Default().GetInt("max_rounds");
static int rounds_passed = 0;

void RoundCounter::Increment()
{
	++rounds_passed;
}

void RoundCounter::Reset()
{
	rounds_passed = 0;
}

bool RoundCounter::IsDone()
{
	return rounds_passed >= max_rounds;
}
