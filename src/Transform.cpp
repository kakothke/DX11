#include "Transform.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Transform::Transform()
	: pos()
	, rot()
	, scale(1)
	, localPos()
	, localRot()
	, localScale(1)
{
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param aPos 位置
/// @param aRot 回転
/// @param aScale 大きさ
Transform::Transform(Vector3 aPos, Vector3 aRot, Vector3 aScale)
	: pos(aPos)
	, rot(Quaternion::Euler(aRot))
	, scale(aScale)
	, localPos()
	, localRot()
	, localScale(1)
{
}

//-------------------------------------------------------------------------------------------------
/// オブジェクトの右方向のベクトルを返す
Vector3 Transform::Right() const
{
	return rot * Vector3(1, 0, 0);
}

//-------------------------------------------------------------------------------------------------
/// オブジェクトの上方向のベクトルを返す
Vector3 Transform::Up() const
{
	return rot * Vector3(0, 1, 0);
}

//-------------------------------------------------------------------------------------------------
/// オブジェクトの前方向のベクトルを返す
Vector3 Transform::Forward() const
{
	return rot * Vector3(0, 0, 1);
}

//-------------------------------------------------------------------------------------------------
/// WorldMatrixに変換して返す
DirectX::XMMATRIX Transform::WorldMatrix() const
{
	Vector3 tmpPos = pos + rot * localPos;
	DirectX::XMMATRIX position = DirectX::XMMatrixTranslation(
		tmpPos.x, tmpPos.y, tmpPos.z
	);
	DirectX::XMMATRIX rotation = DirectX::XMMatrixRotationQuaternion(
		(rot * localRot).XMVECTOR()
	);
	DirectX::XMMATRIX scaling = DirectX::XMMatrixScaling(
		scale.x * localScale.x, scale.y * localScale.y, scale.z * localScale.z
	);
	return scaling * rotation * position;
}

//-------------------------------------------------------------------------------------------------
/// @brief local変数は代入しない
void Transform::operator =(const Transform& aTransform)
{
	pos = aTransform.pos;
	rot = aTransform.rot;
	scale = aTransform.scale;
}

} // namespace
// EOF
