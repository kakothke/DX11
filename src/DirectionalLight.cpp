#include "DirectionalLight.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "ConstantBuffer.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
DirectionalLight::DirectionalLight()
	: mColor(DirectX::XMFLOAT4(1, 0.95f, 0.83f, 1))
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
	ConstantBuffer::getInst()->updateLight(mTransform.rot, mColor);
}

//-------------------------------------------------------------------------------------------------
void DirectionalLight::draw()
{
}

} // namespace
// EOF
