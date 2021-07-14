#pragma once

//-------------------------------------------------------------------------------------------------
#include <vector>

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// ���w�֐��Q
class Math
{
public:
	/// @name ���l�֌W
	//@{
	/// aValue�̕����𒲂ׂ�
	static int Sign(int aValue);
	/// aValue�̕����𒲂ׂ�
	static float Sign(float aValue);
	/// aStart�̒l��aTarget�̒l�܂�aTime�ŕ⊮����
	static float Lerp(float aStart, float aTarget, float aTime);
	/// aValue �̒l���w��͈̔� [aMin, aMax] �ɐ�������
	static int Clamp(int aValue, int aMin, int aMax);
	/// aValue �̒l���w��͈̔� [aMin, aMax] �ɐ�������
	static float Clamp(float aValue, float aMin, float aMax);
	/// aValue�̌�����Ԃ�
	static int Degit(int aValue);
	/// aValue���������Ƃɕ�������
	static std::vector<int> Split(int aValue);
	//@}

private:
	Math();

};

} // namespace
// EOF
