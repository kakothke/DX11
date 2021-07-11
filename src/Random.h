#pragma once

//-------------------------------------------------------------------------------------------------
namespace KDXK {

class Random
{
public:
	static int RandomInt(int aRange);
	static float RandomFloat(int aRange, float aSplit);
	static int RandomSign();
	static void RandomSeed();

private:
	Random();

};

} // namespace
// EOF
