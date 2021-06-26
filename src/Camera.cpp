#include "Camera.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// 定数
const static float DEFAULT_FOV = 60.0f;
const static float DEFAULT_NEAR = 0.3f;
const static float DEFAULT_FAR = 1000.0f;
const static Vector3 DEFAULT_POS = Vector3(0.0f, 1.0f, -10.0f);

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Camera::Camera()
	: mFov(DEFAULT_FOV)
	, mNearZ(DEFAULT_NEAR)
	, mFarZ(DEFAULT_FAR)
{
	mTransform.pos = DEFAULT_POS;
	setTag(GameObjectTag::Camera);
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param aTransform トランスフォーム
Camera::Camera(Transform aTransform)
	: mFov(DEFAULT_FOV)
	, mNearZ(DEFAULT_NEAR)
	, mFarZ(DEFAULT_FAR)
{
	mTransform = aTransform;
	setTag(GameObjectTag::Camera);
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param aCameraParam カメラパラメータ x(Fov) / y(Near) / z(Far)
Camera::Camera(Vector3 aCameraParam)
	: mFov(aCameraParam.x)
	, mNearZ(aCameraParam.y)
	, mFarZ(aCameraParam.z)
{
	mTransform.pos = DEFAULT_POS;
	setTag(GameObjectTag::Camera);
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param aTransform トランスフォーム
/// @param aCameraParam カメラパラメータ x(Fov) / y(Near) / z(Far)
Camera::Camera(Transform aTransform, Vector3 aCameraParam)
	: mFov(aCameraParam.x)
	, mNearZ(aCameraParam.y)
	, mFarZ(aCameraParam.z)
{
	mTransform = aTransform;
	setTag(GameObjectTag::Camera);
}

//-------------------------------------------------------------------------------------------------
/// 更新
void Camera::update()
{
	updateConstantBuffer();
}

//-------------------------------------------------------------------------------------------------
/// 描画
void Camera::draw()
{
}

//-------------------------------------------------------------------------------------------------
/// コンスタントバッファを更新する
void Camera::updateConstantBuffer()
{
	const static auto constantBuffer = Direct3D11::getInst()->getConstantBuffer();
	constantBuffer->setMatrixV(mTransform);
	constantBuffer->setMatrixP(mFov, mNearZ, mFarZ);
	constantBuffer->updateCamera(mTransform.pos);
}

} // namespace
// EOF
