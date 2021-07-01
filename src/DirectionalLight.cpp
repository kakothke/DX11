#include "DirectionalLight.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// 定数
const static Vector3 DEFINE_ANGLE = Vector3(50.0f, -30.0f, 0.0f);
const static Color DEFINE_COLOR = Color(1.0f, 0.9568627f, 0.8392157f, 1.0f);

//-------------------------------------------------------------------------------------------------
/// シングルトンクラス
const static auto D3D11 = Direct3D11::getInst();

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
DirectionalLight::DirectionalLight()
	: mAngle(DEFINE_ANGLE)
	, mColor(DEFINE_COLOR)
{
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param aAngle ライトの向き
DirectionalLight::DirectionalLight(Vector3 aAngle)
	: mAngle(aAngle)
	, mColor(DEFINE_COLOR)
{
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param aColor カラー
DirectionalLight::DirectionalLight(Color aColor)
	: mAngle(DEFINE_ANGLE)
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
