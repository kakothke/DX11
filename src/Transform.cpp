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
	, rot(aRot)
	, scale(aScale)
{
}

//-------------------------------------------------------------------------------------------------
/// XMFLOAT3X3型に変換して返す
DirectX::XMFLOAT3X3 Transform::XMFLOAT3X3() const
{
	return {
		pos.x, pos.y, pos.z,
		rot.x, rot.y, rot.z,
		scale.x, scale.y, scale.z
	};
}

//-------------------------------------------------------------------------------------------------
/// WorldMatrixに変換して返す
DirectX::XMMATRIX Transform::worldMatrix() const
{
	DirectX::XMMATRIX position = DirectX::XMMatrixTranslation(
		pos.x, pos.y, pos.z
	);
	DirectX::XMMATRIX rotation = DirectX::XMMatrixRotationRollPitchYaw(
		rot.x, rot.y, rot.z
	);
	DirectX::XMMATRIX scaling = DirectX::XMMatrixScaling(
		scale.x, scale.y, scale.z
	);
	return scaling * rotation * position;
}

} // namespace
// EOF
