#pragma once

namespace DX11 {

/// 数学関数群
class Math
{
public:
	/// @name 数値関係
	//@{
	/// aValue の値を指定の範囲 [aMin, aMax] に制限する
	static int Clamp(int aValue, int aMin, int aMax);
	/// aValue の値を指定の範囲 [aMin, aMax] に制限する
	static float Clamp(float aValue, float aMin, float aMax);
	//@}

private:
	Math();

};

} // namespace
// EOF
