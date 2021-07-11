#include "Random.h"

//-------------------------------------------------------------------------------------------------
#include <iostream>
#include <time.h>

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
int Random::RandomInt(int aRange)
{
	int out;
	out = rand() % aRange;
	return out;
}

//-------------------------------------------------------------------------------------------------
float Random::RandomFloat(int aRange, float aSplit)
{
	float out;
	out = (rand() % aRange) * aSplit;
	return out;
}

//-------------------------------------------------------------------------------------------------
int Random::RandomSign()
{
	int out;
	out = rand() % 2;
	return (out > 0) - (out == 0);
}

//-------------------------------------------------------------------------------------------------
void Random::RandomSeed()
{
	srand((unsigned int)time(NULL));
}

} // namespace
// EOF
