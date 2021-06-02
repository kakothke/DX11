#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>
#include "Vector3.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// �I�u�W�F�N�g�̈ʒu�A��]�A�X�P�[���������N���X
class Transform
{
public:
	/// @name �R���X�g���N�^
	//@{
	Transform();
	Transform(Vector3 aPos, Vector3 aRot, Vector3 aScale);
	//@}

	//@ name �ϊ��֐�
	//@{
	/// XMFLOAT3X3�^�ɕϊ����ĕԂ�
	DirectX::XMFLOAT3X3 XMFLOAT3X3() const;
	//@}

	/// @name �����o�ϐ�
	//@{
	/// �ʒu
	Vector3 pos;
	/// ��]
	Vector3 rot;
	/// �X�P�[��
	Vector3 scale;
	//@}

};

} // namespace
// EOF
