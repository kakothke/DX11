#include "Math.h"

//-------------------------------------------------------------------------------------------------
#include <algorithm>

//-------------------------------------------------------------------------------------------------
namespace KDXK {

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
