#include "DirectionalLight.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
DirectionalLight::DirectionalLight()
	: mColor(255, 244, 214, 255)
{
	mTransform.rot = Vector3(50, -30, 0);
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param aRot 向き
DirectionalLight::DirectionalLight(Vector3 aRot)
	: mColor(255, 244, 214, 255)
{
	mTransform.rot = aRot;
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param aColor カラー
DirectionalLight::DirectionalLight(Color aColor)
	: mColor(aColor)
{
	mTransform.rot = Vector3(50, -30, 0);
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param aRot 向き
/// @param aColor カラー
DirectionalLight::DirectionalLight(Vector3 aRot, Color aColor)
	: mColor(aColor)
{
	mTransform.rot = aRot;
}

//-------------------------------------------------------------------------------------------------
/// 更新
void DirectionalLight::update()
{
	updateConstantBuffer();
}

//-------------------------------------------------------------------------------------------------
/// 描画
void DirectionalLight::draw()
{
}

//-------------------------------------------------------------------------------------------------
/// コンスタントバッファを更新する
void DirectionalLight::updateConstantBuffer()
{
	Vector3 rot = Vector3(-mTransform.rot.y, mTransform.rot.x, 0).Normalized();
	const static auto cBuf = Direct3D11::getInst()->getConstantBuffer();
	cBuf->updateDLight(rot.XMVECTOR(), mColor.XMFLOAT4());
}

} // namespace
// EOF
