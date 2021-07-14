#include "Math.h"

//-------------------------------------------------------------------------------------------------
#include <algorithm>

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
int Math::Sign(int aValue)
{
	return (aValue > 0) - (aValue < 0);
}

//-------------------------------------------------------------------------------------------------
float Math::Sign(float aValue)
{
	return (float)((aValue > 0) - (aValue < 0));
}

//-------------------------------------------------------------------------------------------------
float Math::Lerp(float aStart, float aTarget, float aTime)
{
	return (1 - aTime) * aStart + aTime * aTarget;
}

//------------------------------------------------------------------------------
int Math::Clamp(int aValue, int aMin, int aMax)
{
	return std::max(std::min(aValue, aMax), aMin);
}

//------------------------------------------------------------------------------
float Math::Clamp(float aValue, float aMin, float aMax)
{
	return std::max(std::min(aValue, aMax), aMin);
}

//-------------------------------------------------------------------------------------------------
int Math::Degit(int aValue)
{
	if (aValue == 0) {
		// 0‚Í1Œ…‚Æ‚µ‚Ä”‚¦‚é
		return 1;
	}
	return (int)log10(aValue) + 1;
}

//-------------------------------------------------------------------------------------------------
std::vector<int> Math::Split(int aValue)
{
	std::vector<int> out = {};
	int degit = Degit(aValue);
	for (int i = 0; i < degit; i++) {
		if (i == 0) {
			out.emplace_back(aValue % 10);
		} else {
			out.emplace_back((aValue / (int)pow(10, i)) % 10);
		}
	}
	return out;
}

} // namespace
// EOF
