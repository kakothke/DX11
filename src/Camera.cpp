#include "Camera.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

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
	Direct3D11::getInst()->getConstantBuffer()->setMatrixV(mTransform);
	Direct3D11::getInst()->getConstantBuffer()->setMatrixP(mFov, mNearZ, mFarZ);
	Direct3D11::getInst()->getConstantBuffer()->updateCamera(mTransform);
}

//-------------------------------------------------------------------------------------------------
void Camera::draw()
{
}

} // namespace
// EOF
