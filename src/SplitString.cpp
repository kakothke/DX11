#pragma once
#include "SplitString.h"

//-------------------------------------------------------------------------------------------------
#include <sstream>

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// �������C�ӂ̃f���~�^�ŕ�������
/// @param aStr �������镶����
/// @param aDelim �������镶�����w��
/// @return ��������������
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
