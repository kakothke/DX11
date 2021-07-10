#include "DirectionalLight.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto D3D11 = Direct3D11::getInst();

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
DirectionalLight::DirectionalLight()
	: mAngle(Vector3(50.0f, -30.0f, 0.0f))
	, mColor(Color(1.0f, 0.9568627f, 0.8392157f, 1.0f))
{
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param aAngle ライトの向き
DirectionalLight::DirectionalLight(Vector3 aAngle)
	: mAngle(aAngle)
	, mColor(Color(1.0f, 0.9568627f, 0.8392157f, 1.0f))
{
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param aColor カラー
DirectionalLight::DirectionalLight(Color aColor)
	: mAngle(Vector3(50.0f, -30.0f, 0.0f))
	, mColor(aColor)
{
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param aAngle ライトの向き
/// @param aColor カラー
DirectionalLight::DirectionalLight(Vector3 aAngle, Color aColor)
	: mAngle(aAngle)
	, mColor(aColor)
{
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
DirectionalLight::~DirectionalLight()
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
	D3D11->getConstantBuffer()->updateDLight(mAngle, mColor);
}

} // namespace
// EOF
