#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>
#include "Vector3.h"
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

	/// @ name �ϊ��֐�
	//@{
	/// �I�u�W�F�N�g�̉E�����̃x�N�g����Ԃ�
	Vector3 Right() const;
	/// �I�u�W�F�N�g�̏�����̃x�N�g����Ԃ�
	Vector3 Up() const;
	/// �I�u�W�F�N�g�̑O�����̃x�N�g����Ԃ�
	Vector3 Forward() const;
	/// WorldMatrix�ɕϊ����ĕԂ�
	DirectX::XMMATRIX WorldMatrix() const;
	//@}

	/// @name ���Z�q�I�[�o�[���[�h
	//@{
	void operator =(const Transform& aTransform);
	//@}

	/// @name �����o�ϐ�
	//@{
	/// �ʒu
	Vector3 pos;
	/// ��]
	Quaternion rot;
	/// �X�P�[��
	Vector3 scale;
	/// �e����̈ʒu
	Vector3 localPos;
	/// �e����̉�]
	Quaternion localRot;
	/// �e����̃X�P�[��
	Vector3 localScale;
	//@}

};

} // namespace
// EOF
