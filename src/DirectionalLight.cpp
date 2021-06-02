#include "DirectionalLight.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
DirectionalLight::DirectionalLight()
	: mColor(255, 244, 214, 255)
{
	mTransform.rot = Vector3(50, -30, 0);
}

//-------------------------------------------------------------------------------------------------
void DirectionalLight::update()
{
	updateConstantBuffer();
}

//-------------------------------------------------------------------------------------------------
void DirectionalLight::updateConstantBuffer()
{
	Vector3 rot = Vector3(-mTransform.rot.y, mTransform.rot.x, 0).Normalized();
	Direct3D11::getInst()->getConstantBuffer()->updateDLight(rot.XMVECTOR(), mColor.XMFLOAT4());
}

//-------------------------------------------------------------------------------------------------
void DirectionalLight::draw()
{
}

} // namespace
// EOF
