#pragma once

//-------------------------------------------------------------------------------------------------
#include <vector>
#include <string>

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// �x�N�g���ϊ��v�Z
class SplitString
{
public:
	//@ name �������C�ӂ̃f���~�^�ŕ�������
	//@{
	static std::vector<std::string> split(const std::string& aStr, const char aDelim);
	//@}

private:
	SplitString();

};

} // namespace
// EOF
