#include "Transform.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Transform::Transform()
	: pos()
	, rot(DirectX::XMQuaternionIdentity())
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
	, rot(DirectX::XMQuaternionRotationRollPitchYaw(aRot.x, aRot.y, aRot.z))
	, scale(aScale)
{
}

//-------------------------------------------------------------------------------------------------
/// WorldMatrixに変換して返す
DirectX::XMMATRIX Transform::worldMatrix() const
{
	DirectX::XMMATRIX position = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
	DirectX::XMMATRIX rotation = DirectX::XMMatrixRotationQuaternion(rot);
	DirectX::XMMATRIX scaling = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
	return scaling * rotation * position;
}

} // namespace
// EOF
