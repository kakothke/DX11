#include "Camera.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "ConstantBuffer.h"
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
	mTransform.rot.z += 0.001f;
	updateConstantBuffer();
}

//-------------------------------------------------------------------------------------------------
void Camera::updateConstantBuffer()
{
	ConstantBuffer::getInst()->setMatrixV(mTransform);
	ConstantBuffer::getInst()->setMatrixP(mFov, mNearZ, mFarZ);
	ConstantBuffer::getInst()->updateCamera(mTransform);
}

//-------------------------------------------------------------------------------------------------
void Camera::draw()
{
}

} // namespace
// EOF
