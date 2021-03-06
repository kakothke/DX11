#include "BaseCamera.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto D3D11 = Direct3D11::getInst();

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
BaseCamera::BaseCamera()
	: mFov(60.0f)
	, mNearZ(0.3f)
	, mFarZ(1000.0f)
{
	mTransform.pos = Vector3(0.0f, 1.0f, -10.0f);
	setTag(GameObjectTag::Camera);
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param aTransform トランスフォーム
BaseCamera::BaseCamera(Transform aTransform)
	: mFov(60.0f)
	, mNearZ(0.3f)
	, mFarZ(1000.0f)
{
	mTransform = aTransform;
	setTag(GameObjectTag::Camera);
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param aCameraParam カメラパラメータ x(Fov) / y(Near) / z(Far)
BaseCamera::BaseCamera(Vector3 aCameraParam)
	: mFov(aCameraParam.x)
	, mNearZ(aCameraParam.y)
	, mFarZ(aCameraParam.z)
{
	mTransform.pos = Vector3(0.0f, 1.0f, -10.0f);
	setTag(GameObjectTag::Camera);
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param aTransform トランスフォーム
/// @param aCameraParam カメラパラメータ x(Fov) / y(Near) / z(Far)
BaseCamera::BaseCamera(Transform aTransform, Vector3 aCameraParam)
	: mFov(aCameraParam.x)
	, mNearZ(aCameraParam.y)
	, mFarZ(aCameraParam.z)
{
	mTransform = aTransform;
	setTag(GameObjectTag::Camera);
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
BaseCamera::~BaseCamera()
{
}

//-------------------------------------------------------------------------------------------------
/// 更新
void BaseCamera::update()
{
}

//-------------------------------------------------------------------------------------------------
/// 描画
void BaseCamera::draw()
{
}

//-------------------------------------------------------------------------------------------------
/// コンスタントバッファを更新する
void BaseCamera::updateConstantBuffer()
{	
	D3D11->getConstantBuffer()->setMatrixV(mTransform);
	D3D11->getConstantBuffer()->setMatrixP(mFov, mNearZ, mFarZ);
	D3D11->getConstantBuffer()->updateCamera(mTransform.pos);
}

} // namespace
// EOF
