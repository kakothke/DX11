#include "Transform.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Transform::Transform()
	: pos()
	, rot()
	, scale(1, 1, 1)
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
{
}

//-------------------------------------------------------------------------------------------------
/// オブジェクトの右方向のベクトルを返す
Vector3 Transform::Right()
{
	return rot * Vector3(1, 0, 0);
}

//-------------------------------------------------------------------------------------------------
/// オブジェクトの上方向のベクトルを返す
Vector3 Transform::Up()
{
	return rot * Vector3(0, 1, 0);
}

//-------------------------------------------------------------------------------------------------
/// オブジェクトの前方向のベクトルを返す
Vector3 Transform::Forward()
{
	return rot * Vector3(0, 0, 1);
}

//-------------------------------------------------------------------------------------------------
/// WorldMatrixに変換して返す
DirectX::XMMATRIX Transform::WorldMatrix() const
{
	DirectX::XMMATRIX position = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
	DirectX::XMMATRIX rotation = DirectX::XMMatrixRotationQuaternion(rot.XMVECTOR());
	DirectX::XMMATRIX scaling = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
	return scaling * rotation * position;
}

} // namespace
// EOF
