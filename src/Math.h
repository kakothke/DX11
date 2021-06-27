#pragma once

namespace KDXK {

/// ���w�֐��Q
class Math
{
public:
	/// @name ���l�֌W
	//@{
	/// aStart�̒l��aTarget�̒l�܂�aTime�ŕ⊮����
	static float Lerp(float aStart, float aTarget, float aTime);
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
