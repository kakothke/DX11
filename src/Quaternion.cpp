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
Quaternion Quaternion::AxisAngle(Vector3 aAxis, float aAngle)
{
	Quaternion out;
	if (aAxis != Vector3()) {
		out.mQuaternion = DirectX::XMQuaternionRotationAxis(aAxis.XMVECTOR(), aAngle);
	}
	return out;
}

//-------------------------------------------------------------------------------------------------
/// オイラー角で回転を作成する
/// @param aEulerAngle オイラー角
Quaternion Quaternion::Euler(Vector3 aEulerAngle)
{
	Quaternion out;
	out.mQuaternion = DirectX::XMQuaternionRotationRollPitchYaw(aEulerAngle.x, aEulerAngle.y, aEulerAngle.z);
	return out;
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
