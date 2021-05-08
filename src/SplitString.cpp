#pragma once
#include "SplitString.h"

//-------------------------------------------------------------------------------------------------
#include <sstream>

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// •¶š—ñ‚ğ”CˆÓ‚ÌƒfƒŠƒ~ƒ^‚Å•ªŠ„‚·‚é
/// @param aStr •ªŠ„‚·‚é•¶š—ñ
/// @param aDelim ‹æØ‚é•¶š
/// @return ‹æØ‚Á‚½•¶š—ñ
std::vector<std::string> SplitString::split(const std::string& aStr, const char aDelim)
{
    std::vector<std::string> v;
    std::istringstream iss(aStr);
    std::string buf;

    while (getline(iss, buf, aDelim)) {
        v.push_back(buf);
    }

    return v;
}

} // namespace
// EOF
