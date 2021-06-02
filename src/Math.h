#pragma once

namespace DX11 {

/// ���w�֐��Q
class Math
{
public:
	/// @name ���l�֌W
	//@{
	/// aValue �̒l���w��͈̔� [aMin, aMax] �ɐ�������
	static int Clamp(int aValue, int aMin, int aMax);
	/// aValue �̒l���w��͈̔� [aMin, aMax] �ɐ�������
	static float Clamp(float aValue, float aMin, float aMax);
	//@}

private:
	Math();

};

} // namespace
// EOF
