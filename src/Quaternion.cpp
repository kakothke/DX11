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
/// @param aQuaternion DirectXMath�ō쐬���ꂽ�N�H�[�^�j�I��
Quaternion::Quaternion(DirectX::XMVECTOR aQuaternion)
{
	mQuaternion = aQuaternion;
}

//-------------------------------------------------------------------------------------------------
/// Axis�̎����Angle�x��]�����]���쐬����
/// @param aAxis ��]����
/// @param aAngle ��]�x
Quaternion Quaternion::AxisAngle(Vector3 aAxis, float aAngle)
{
	Quaternion out;
	if (aAxis != Vector3()) {
		aAngle *= DirectX::XM_PI / 180;
		out.mQuaternion = DirectX::XMQuaternionRotationAxis(aAxis.XMVECTOR(), aAngle);
	}
	return out;
}

//-------------------------------------------------------------------------------------------------
/// �I�C���[�p�ŉ�]���쐬����
/// @param aEulerAngle �I�C���[�p
Quaternion Quaternion::Euler(Vector3 aEulerAngle)
{
	Quaternion out;
	aEulerAngle *= DirectX::XM_PI / 180;
	out.mQuaternion = DirectX::XMQuaternionRotationRollPitchYawFromVector(aEulerAngle.XMVECTOR());
	return out;
}

//-------------------------------------------------------------------------------------------------
/// XMVECTOR�̃����o�ϐ���Ԃ�
/// @return 
const DirectX::XMVECTOR& Quaternion::XMVECTOR() const
{
	return mQuaternion;
}

//-------------------------------------------------------------------------------------------------
/// �t�N�H�[�^�j�I�����쐬����
Quaternion Quaternion::operator -() const
{
	Quaternion out;
	out.mQuaternion = DirectX::XMQuaternionInverse(mQuaternion);
	return out;
}

//-------------------------------------------------------------------------------------------------
/// Vector3����]������
Vector3 Quaternion::operator *(const Vector3& aVector) const
{
	DirectX::XMVECTOR out = aVector.XMVECTOR();
	DirectX::XMMATRIX rotMatrix = DirectX::XMMatrixRotationQuaternion(mQuaternion);
	out = DirectX::XMVector3TransformCoord(out, rotMatrix);
	return {
		out.m128_f32[0],
		out.m128_f32[1],
		out.m128_f32[2]
	};
}

//-------------------------------------------------------------------------------------------------
/// Vector2����]������
Vector2 Quaternion::operator *(const Vector2& aVector) const
{
	DirectX::XMVECTOR out = aVector.XMVECTOR();
	DirectX::XMMATRIX rotMatrix = DirectX::XMMatrixRotationQuaternion(mQuaternion);
	out = DirectX::XMVector3TransformCoord(out, rotMatrix);
	return {
		out.m128_f32[0],
		out.m128_f32[1]
	};
}

//-------------------------------------------------------------------------------------------------
/// �N�H�[�^�j�I�����m����Z����*
Quaternion Quaternion::operator *(const Quaternion& aQuaternion) const
{
	Quaternion out;
	out.mQuaternion = DirectX::XMQuaternionMultiply(mQuaternion, aQuaternion.mQuaternion);
	return out;
}

//-------------------------------------------------------------------------------------------------
/// �N�H�[�^�j�I�����m����Z����*=
void Quaternion::operator *=(const Quaternion& aQuaternion)
{
	mQuaternion = DirectX::XMQuaternionMultiply(mQuaternion, aQuaternion.mQuaternion);
}

//-------------------------------------------------------------------------------------------------
/// ���l���Z�q==
bool Quaternion::operator ==(const Quaternion& aQuaternion) const
{
	if (mQuaternion.m128_f32[0] == aQuaternion.mQuaternion.m128_f32[0] &&
		mQuaternion.m128_f32[1] == aQuaternion.mQuaternion.m128_f32[1] &&
		mQuaternion.m128_f32[2] == aQuaternion.mQuaternion.m128_f32[2] &&
		mQuaternion.m128_f32[3] == aQuaternion.mQuaternion.m128_f32[3]) {
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
/// ���l���Z�q!=
bool Quaternion::operator !=(const Quaternion& aQuaternion) const
{
	if (mQuaternion.m128_f32[0] != aQuaternion.mQuaternion.m128_f32[0] ||
		mQuaternion.m128_f32[1] != aQuaternion.mQuaternion.m128_f32[1] ||
		mQuaternion.m128_f32[2] != aQuaternion.mQuaternion.m128_f32[2] ||
		mQuaternion.m128_f32[3] != aQuaternion.mQuaternion.m128_f32[3]) {
		return true;
	}
	return false;
}

} // namespace
// EOF
