#include "DirectionalLight.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
DirectionalLight::DirectionalLight()
	: mEulerAngle(50, -30, 0)
	, mColor(255, 244, 214, 255)
{
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param aRot 向き
DirectionalLight::DirectionalLight(Vector3 aAngle)
	: mEulerAngle(aAngle)
	, mColor(255, 244, 214, 255)
{
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param aColor カラー
DirectionalLight::DirectionalLight(Color aColor)
	: mEulerAngle(50, -30, 0)
	, mColor(aColor)
{
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param aRot 向き
/// @param aColor カラー
DirectionalLight::DirectionalLight(Vector3 aAngle, Color aColor)
	: mEulerAngle(aAngle)
	, mColor(aColor)
{
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
	const static auto cBuf = Direct3D11::getInst()->getConstantBuffer();
	cBuf->updateDLight(mEulerAngle, mColor);
}

} // namespace
// EOF
