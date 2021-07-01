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
	return (aValue > 0) - (aValue < 0);
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

} // namespace
// EOF
