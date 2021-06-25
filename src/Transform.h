#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>
#include "Vector3.h"
#include "Vector2.h"
#include "Quaternion.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

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
	/// WorldMatrix�ɕϊ����ĕԂ�
	DirectX::XMMATRIX worldMatrix() const;
	//@}

	/// @name �����o�ϐ�
	//@{
	/// �ʒu
	Vector3 pos;
	/// ��]
	Quaternion rot;
	/// �X�P�[��
	Vector3 scale;
	//@}

};

} // namespace
// EOF
