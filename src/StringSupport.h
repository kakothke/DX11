#pragma once

//-------------------------------------------------------------------------------------------------
#include <vector>
#include <string>

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// ベクトル変換計算
class StringSupport
{
public:
	//@ name 文字列を任意のデリミタで分割する
	//@{
	static std::vector<std::string> split(const std::string& aStr, const char aDelim);
	//@}

private:
	StringSupport();

};

} // namespace
// EOF
