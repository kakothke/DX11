#include "Transform.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

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

} // namespace
// EOF
