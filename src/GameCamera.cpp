#include "GameCamera.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
GameCamera::GameCamera()
{
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param aTransform トランスフォーム
GameCamera::GameCamera(Transform aTransform) : Camera(aTransform)
{
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param aCameraParam カメラパラメータ x(Fov) / y(Near) / z(Far)
GameCamera::GameCamera(Vector3 aCameraParam) : Camera(aCameraParam)
{
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param aTransform トランスフォーム
/// @param aCameraParam カメラパラメータ x(Fov) / y(Near) / z(Far)
GameCamera::GameCamera(Transform aTransform, Vector3 aCameraParam) : Camera(aTransform, aCameraParam)
{
}

//-------------------------------------------------------------------------------------------------
/// 更新
void GameCamera::update()
{
	updateConstantBuffer();
}

//-------------------------------------------------------------------------------------------------
/// 描画
void GameCamera::draw()
{
}

} // namespace
// EOF
