#include "Quaternion.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Quaternion::Quaternion()
	: mQuaternion(DirectX::XMQuaternionIdentity())
{
}

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
/// @param x 
/// @param y 
/// @param z 
/// @param w 
Quaternion::Quaternion(float x, float y, float z, float w)
	: mQuaternion(DirectX::XMVectorSet(x, y, z, w))
{
}

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
/// @param aEulerAngle �I�C���[�p
Quaternion::Quaternion(Vector3 aEulerAngle)
	: mQuaternion(DirectX::XMQuaternionRotationRollPitchYaw(aEulerAngle.x, aEulerAngle.y, aEulerAngle.z))
{
}

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
/// @param aAxis ��]����
/// @param aAngle ��]�x
Quaternion::Quaternion(Vector3 aAxis, float aAngle)
	: mQuaternion(DirectX::XMQuaternionIdentity())
{
	if (aAxis != Vector3()) {
		mQuaternion = DirectX::XMQuaternionRotationAxis(aAxis.XMVECTOR(), aAngle);
	}
}

//-------------------------------------------------------------------------------------------------
/// Axis�̎����Angle�x��]�����]���쐬����
/// @param aAxis ��]����
/// @param aAngle ��]�x
void Quaternion::axisAngle(Vector3 aAxis, float aAngle)
{
	if (aAxis != Vector3()) {
		mQuaternion = DirectX::XMQuaternionRotationAxis(aAxis.XMVECTOR(), aAngle);
	}
}

//-------------------------------------------------------------------------------------------------
/// �I�C���[�p�ŉ�]���쐬����
/// @param aEulerAngle �I�C���[�p
void Quaternion::euler(Vector3 aEulerAngle)
{
	mQuaternion = DirectX::XMQuaternionRotationRollPitchYaw(aEulerAngle.x, aEulerAngle.y, aEulerAngle.z);
}

//-------------------------------------------------------------------------------------------------
/// XMVECTOR�̃����o�ϐ���Ԃ�
/// @return 
const DirectX::XMVECTOR& Quaternion::XMVECTOR() const
{
	return mQuaternion;
}

//-------------------------------------------------------------------------------------------------
Quaternion Quaternion::operator -() const
{
	Quaternion out;
	out.mQuaternion = DirectX::XMQuaternionInverse(mQuaternion);
	return out;
}

DirectX::XMVECTOR Quaternion::operator *(const Quaternion& aQuaternion) const
{
	return DirectX::XMQuaternionMultiply(mQuaternion, aQuaternion.mQuaternion);
}

//-------------------------------------------------------------------------------------------------
void Quaternion::operator =(const DirectX::XMVECTOR& aQuaternion)
{
	mQuaternion = aQuaternion;
}

void Quaternion::operator =(const Vector3& aEulerAngle)
{
	mQuaternion = DirectX::XMQuaternionRotationRollPitchYaw(aEulerAngle.x, aEulerAngle.y, aEulerAngle.z);
}

void Quaternion::operator *=(const Quaternion& aQuaternion)
{
	mQuaternion = operator*(aQuaternion);
}

} // namespace
// EOF
