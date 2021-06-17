#include "Camera.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Camera::Camera()
	: mFov(60)
	, mNearZ(0.3f)
	, mFarZ(1000)
	, mCBuf(Direct3D11::getInst()->getConstantBuffer())
{
	mTransform.pos = Vector3(0, 1, -10);
	setTag(GameObjectTag::Camera);
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param aTransform トランスフォーム
Camera::Camera(Transform aTransform)
	: mFov(60)
	, mNearZ(0.3f)
	, mFarZ(1000)
	, mCBuf(Direct3D11::getInst()->getConstantBuffer())
{
	mTransform = aTransform;
	setTag(GameObjectTag::Camera);
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param aCameraParam カメラパラメータ
Camera::Camera(Vector3 aCameraParam)
	: mFov(aCameraParam.x)
	, mNearZ(aCameraParam.y)
	, mFarZ(aCameraParam.z)
	, mCBuf(Direct3D11::getInst()->getConstantBuffer())
{
	mTransform.pos = Vector3(0, 1, -10);
	setTag(GameObjectTag::Camera);
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param aTransform トランスフォーム
/// @param aCameraParam カメラパラメータ
Camera::Camera(Transform aTransform, Vector3 aCameraParam)
	: mFov(aCameraParam.x)
	, mNearZ(aCameraParam.y)
	, mFarZ(aCameraParam.z)
	, mCBuf(Direct3D11::getInst()->getConstantBuffer())
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
	DirectX::XMFLOAT3 camera(mFov, mNearZ, mFarZ);
	mCBuf->setMatrixVP(mTransform.XMFLOAT3X3(), camera);
	mCBuf->updateCamera(mTransform.pos.XMVECTOR(), mTransform.rot.XMVECTOR());
}

} // namespace
// EOF
