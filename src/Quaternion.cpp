#include "Quaternion.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Quaternion::Quaternion()
	: mQuaternion(DirectX::XMQuaternionIdentity())
{
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param x 
/// @param y 
/// @param z 
/// @param w 
Quaternion::Quaternion(float x, float y, float z, float w)
	: mQuaternion(DirectX::XMVectorSet(x, y, z, w))
{
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param aEulerAngle オイラー角
Quaternion::Quaternion(Vector3 aEulerAngle)
	: mQuaternion(DirectX::XMQuaternionRotationRollPitchYaw(aEulerAngle.x, aEulerAngle.y, aEulerAngle.z))
{
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param aAxis 回転方向
/// @param aAngle 回転度
Quaternion::Quaternion(Vector3 aAxis, float aAngle)
	: mQuaternion(DirectX::XMQuaternionIdentity())
{
	if (aAxis != Vector3()) {
		mQuaternion = DirectX::XMQuaternionRotationAxis(aAxis.XMVECTOR(), aAngle);
	}
}

//-------------------------------------------------------------------------------------------------
/// Axisの周りをAngle度回転する回転を作成する
/// @param aAxis 回転方向
/// @param aAngle 回転度
void Quaternion::axisAngle(Vector3 aAxis, float aAngle)
{
	if (aAxis != Vector3()) {
		mQuaternion = DirectX::XMQuaternionRotationAxis(aAxis.XMVECTOR(), aAngle);
	}
}

//-------------------------------------------------------------------------------------------------
/// オイラー角で回転を作成する
/// @param aEulerAngle オイラー角
void Quaternion::euler(Vector3 aEulerAngle)
{
	mQuaternion = DirectX::XMQuaternionRotationRollPitchYaw(aEulerAngle.x, aEulerAngle.y, aEulerAngle.z);
}

//-------------------------------------------------------------------------------------------------
/// XMVECTORのメンバ変数を返す
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
