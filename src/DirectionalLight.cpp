#include "DirectionalLight.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

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
	static auto constantBuf = Direct3D11::getInst()->getConstantBuffer();
	constantBuf->updateDLight(rot.XMVECTOR(), mColor.XMFLOAT4());
}

//-------------------------------------------------------------------------------------------------
void DirectionalLight::draw()
{
}

} // namespace
// EOF
