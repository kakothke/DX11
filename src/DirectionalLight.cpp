#include "DirectionalLight.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// 定数
static const Vector3 DEFAULT_ANGLE = Vector3(50.0f, -30.0f, 0.0f);
static const Color DEFAULT_COLOR = Color(1.0f, 0.9568627f, 0.8392157f, 1.0f);

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
DirectionalLight::DirectionalLight()
	: mAngle(DEFAULT_ANGLE)
	, mColor(DEFAULT_COLOR)
{
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param aAngle ライトの向き
DirectionalLight::DirectionalLight(Vector3 aAngle)
	: mAngle(aAngle)
	, mColor(DEFAULT_COLOR)
{
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param aColor カラー
DirectionalLight::DirectionalLight(Color aColor)
	: mAngle(DEFAULT_ANGLE)
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
	cBuf->updateDLight(mAngle, mColor);
}

} // namespace
// EOF
