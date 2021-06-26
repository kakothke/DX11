#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>
#include "Vector3.h"
#include "Vector2.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �O���錾
class Vector3;
class Vector2;

/// �N�H�[�^�j�I��
class Quaternion
{
public:
	/// @name �R���X�g���N�^
	//@{
	Quaternion();
	Quaternion(float x, float y, float z, float w);
	Quaternion(DirectX::XMVECTOR aQuaternion);
	//@}

	/// @name �N�H�[�^�j�I���쐬�֐�
	//@{
	/// Axis�̎����Angle�x��]�����]���쐬����
	static Quaternion AxisAngle(Vector3 aAxis, float aAngle);
	/// �I�C���[�p�ŉ�]���쐬����
	static Quaternion Euler(Vector3 aEulerAngle);
	//@}

	/// @name �ϊ��֐�
	//@{
	/// XMVECTOR�̃����o�ϐ���Ԃ�
	const DirectX::XMVECTOR& XMVECTOR() const;
	//@}

	/// @name ���Z�q�I�[�o�[���[�h
	//@{
	/// �t�N�H�[�^�j�I�����쐬����
	Quaternion operator -() const;
	/// Vector3����]������
	Vector3 operator *(const Vector3& aVector) const;
	/// Vector2����]������
	Vector2 operator *(const Vector2& aVector) const;
	/// �N�H�[�^�j�I�����m�̏�Z*
	Quaternion operator *(const Quaternion& aQuaternion) const;
	/// �N�H�[�^�j�I�����m�̏�Z*=
	void operator *=(const Quaternion& aQuaternion);
	/// ���l���Z�q==
	bool operator ==(const Quaternion& aQuaternion) const;
	/// ���l���Z�q!=
	bool operator !=(const Quaternion& aQuaternion) const;
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// DirectXMath�N�H�[�^�j�I��
	DirectX::XMVECTOR mQuaternion;
	//@}

};

} // namespace
// EOF
