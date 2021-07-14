#pragma once

//-------------------------------------------------------------------------------------------------
#include <vector>

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// 数学関数群
class Math
{
public:
	/// @name 数値関係
	//@{
	/// aValueの符号を調べる
	static int Sign(int aValue);
	/// aValueの符号を調べる
	static float Sign(float aValue);
	/// aStartの値をaTargetの値までaTimeで補完する
	static float Lerp(float aStart, float aTarget, float aTime);
	/// aValue の値を指定の範囲 [aMin, aMax] に制限する
	static int Clamp(int aValue, int aMin, int aMax);
	/// aValue の値を指定の範囲 [aMin, aMax] に制限する
	static float Clamp(float aValue, float aMin, float aMax);
	/// aValueの桁数を返す
	static int Degit(int aValue);
	/// aValueを桁数ごとに分解する
	static std::vector<int> Split(int aValue);
	//@}

private:
	Math();

};

} // namespace
// EOF
