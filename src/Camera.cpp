#include "Camera.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
Camera::Camera()
	: mFov(60)
	, mNearZ(0.3f)
	, mFarZ(1000)
{
	mTransform.pos = Vector3(0, 1, -10);
	setTag(GameObjectTag::Camera);
}

//-------------------------------------------------------------------------------------------------
void Camera::update()
{
	updateConstantBuffer();
}

//-------------------------------------------------------------------------------------------------
void Camera::updateConstantBuffer()
{
	DirectX::XMFLOAT3 camera(mFov, mNearZ, mFarZ);
	static auto constantBuf = Direct3D11::getInst()->getConstantBuffer();
	constantBuf->setMatrixVP(mTransform.XMFLOAT3X3(), camera);
	constantBuf->updateCamera(mTransform.pos.XMVECTOR(), mTransform.rot.XMVECTOR());
}

//-------------------------------------------------------------------------------------------------
void Camera::draw()
{
}

} // namespace
// EOF
