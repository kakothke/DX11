#pragma once
#include "SplitString.h"

//-------------------------------------------------------------------------------------------------
#include <sstream>

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// 文字列を任意のデリミタで分割する
/// @param aStr 分割する文字列
/// @param aDelim 分割する文字を指定
/// @return 分割した文字列
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
