#include "Camera.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// 定数
const static float DEFINE_FOV = 60.0f;
const static float DEFINE_NEAR = 0.3f;
const static float DEFINE_FAR = 1000.0f;
const static Vector3 DEFINE_POS = Vector3(0.0f, 1.0f, -10.0f);

//-------------------------------------------------------------------------------------------------
/// シングルトンクラス
const static auto D3D11 = Direct3D11::getInst();

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Camera::Camera()
	: mFov(DEFINE_FOV)
	, mNearZ(DEFINE_NEAR)
	, mFarZ(DEFINE_FAR)
{
	mTransform.pos = DEFINE_POS;
	setTag(GameObjectTag::Camera);
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param aTransform トランスフォーム
Camera::Camera(Transform aTransform)
	: mFov(DEFINE_FOV)
	, mNearZ(DEFINE_NEAR)
	, mFarZ(DEFINE_FAR)
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
	mTransform.pos = DEFINE_POS;
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
	D3D11->getConstantBuffer()->setMatrixV(mTransform);
	D3D11->getConstantBuffer()->setMatrixP(mFov, mNearZ, mFarZ);
	D3D11->getConstantBuffer()->updateCamera(mTransform.pos);
}

} // namespace
// EOF
