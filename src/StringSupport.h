#pragma once

//-------------------------------------------------------------------------------------------------
#include <vector>
#include <string>

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �x�N�g���ϊ��v�Z
class StringSupport
{
public:
	//@ name �������C�ӂ̃f���~�^�ŕ�������
	//@{
	static std::vector<std::string> split(const std::string& aStr, const char aDelim);
	//@}

private:
	StringSupport();

};

} // namespace
// EOF
