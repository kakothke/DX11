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
/// @param aQuaternion DirectXMathで作成されたクォータニオン
Quaternion::Quaternion(DirectX::XMVECTOR aQuaternion)
{
	mQuaternion = aQuaternion;
}

//-------------------------------------------------------------------------------------------------
/// Axisの周りをAngle度回転する回転を作成する
/// @param aAxis 回転方向
/// @param aAngle 回転度
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
/// オイラー角で回転を作成する
/// @param aEulerAngle オイラー角
Quaternion Quaternion::Euler(Vector3 aEulerAngle)
{
	Quaternion out;
	aEulerAngle *= DirectX::XM_PI / 180;
	out.mQuaternion = DirectX::XMQuaternionRotationRollPitchYawFromVector(aEulerAngle.XMVECTOR());
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
/// 逆クォータニオンを作成する
Quaternion Quaternion::operator -() const
{
	Quaternion out;
	out.mQuaternion = DirectX::XMQuaternionInverse(mQuaternion);
	return out;
}

//-------------------------------------------------------------------------------------------------
/// Vector3を回転させる
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
/// Vector2を回転させる
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
/// クォータニオン同士を乗算する*
Quaternion Quaternion::operator *(const Quaternion& aQuaternion) const
{
	Quaternion out;
	out.mQuaternion = DirectX::XMQuaternionMultiply(mQuaternion, aQuaternion.mQuaternion);
	return out;
}

//-------------------------------------------------------------------------------------------------
/// クォータニオン同士を乗算する*=
void Quaternion::operator *=(const Quaternion& aQuaternion)
{
	mQuaternion = DirectX::XMQuaternionMultiply(mQuaternion, aQuaternion.mQuaternion);
}

//-------------------------------------------------------------------------------------------------
/// 等値演算子==
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
/// 等値演算子!=
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
