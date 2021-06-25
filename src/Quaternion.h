#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>
#include "Vector3.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �N�H�[�^�j�I��
class Quaternion
{
public:
	/// @name �R���X�g���N�^
	//@{
	Quaternion();
	Quaternion(float x, float y, float z, float w);
	Quaternion(Vector3 aEulerAngle);
	Quaternion(Vector3 aAxis, float aAngle);
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
	Quaternion operator -() const;
	DirectX::XMVECTOR operator *(const Quaternion& aQuaternion) const;

	bool operator ==(const Quaternion& aQuaternion) const;
	bool operator !=(const Quaternion& aQuaternion) const;

	void operator =(const DirectX::XMVECTOR& aQuaternion);
	void operator =(const Vector3& aEulerAngle);
	void operator *=(const Quaternion& aQuaternion);
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	DirectX::XMVECTOR mQuaternion;
	//@}

};

} // namespace
// EOF
