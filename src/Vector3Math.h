#pragma once

//-------------------------------------------------------------------------------------------------
#include "Vector3.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// �x�N�g���ϊ��v�Z
class Vector3Math
{
public:
	//@ name �ϊ��֐�
	//@{
	/// �x�N�g���̒�����Ԃ�
	static float Magnitude(Vector3 aVector);
	/// ������1�ɕϊ������x�N�g����Ԃ�
	static Vector3 Normalized(Vector3 aVector);
	/// XMFLOAT3�^�ɕϊ����ĕԂ�
	static const DirectX::XMFLOAT3& XMFLOAT3(Vector3 aVector);
	//@}

private:
	Vector3Math();

};

} // namespace
// EOF
