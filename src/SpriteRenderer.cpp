#include "SpriteRenderer.h"

//-------------------------------------------------------------------------------------------------
#include "Math.h"
#include "TextureLoader.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// シングルトンクラス
const static auto D3D11 = Direct3D11::getInst();
const static auto TEXTURE_LOADER = TextureLoader::getInst();
const static auto SPRITE_LOADER = SpriteLoader::getInst();
const static auto SHADER_LOADER = ShaderLoader::getInst();

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
SpriteRenderer::SpriteRenderer()
	: mSpriteData()
	, mShaderData()
	, mColor()
	, mPivot(0.5f, 0.5f)
	, mAnchor(0.0f, 0.0f)
	, mSplit(1.0f, 1.0f)
{
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
SpriteRenderer::~SpriteRenderer()
{
}

//-------------------------------------------------------------------------------------------------
/// 描画
/// @param aTransform トランスフォーム
void SpriteRenderer::render(const Transform& aTransform)
{
	// 読み込みチェック
	if (!mSpriteData || !mShaderData) {
		return;
	}

	// プリミティブの形状を指定
	D3D11->getContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// シェーダーの指定
	D3D11->setShader(mShaderData);

	UINT strides = sizeof(SpriteLoader::SpriteVertex);
	UINT offsets = 0;

	// IAに設定する頂点バッファの指定
	D3D11->getContext()->IASetVertexBuffers(0, 1, &mSpriteData->vertexBuffer, &strides, &offsets);

	// コンスタントバッファを更新
	D3D11->getConstantBuffer()->updateColor(mColor, mColor);
	D3D11->getConstantBuffer()->setSpriteSplit(mSplit);
	D3D11->getConstantBuffer()->setSpriteMatrixW(aTransform, mPivot);
	D3D11->getConstantBuffer()->updateSprite();

	// テクスチャーセット	
	D3D11->setTexture(TEXTURE_LOADER->getTexture(mSpriteData->fileName));

	// 描画
	D3D11->getContext()->Draw(4, 0);
}

//-------------------------------------------------------------------------------------------------
/// スプライトを設定する
/// @param aFileName ファイルパス
void SpriteRenderer::setSprite(const LPCSTR aFileName)
{
	mSpriteData = SPRITE_LOADER->getSpriteData(aFileName);
}

//-------------------------------------------------------------------------------------------------
/// シェーダーを設定する
/// @param aFileName ファイルパス
void SpriteRenderer::setShader(const LPCSTR aFileName)
{
	mShaderData = SHADER_LOADER->getShaderData(aFileName);
}

//-------------------------------------------------------------------------------------------------
/// カラーを設定する
/// @param aColor カラー
void SpriteRenderer::setColor(const Color& aColor)
{
	mColor = aColor;
}

//-------------------------------------------------------------------------------------------------
/// 描画原点を設定する
/// @param aX 原点x(-1~1)
/// @param aY 原点y(-1~1)
void SpriteRenderer::setPivot(float aX, float aY)
{
	aX = Math::Clamp(aX, -1.0f, 1.0f);
	aY = Math::Clamp(aY, -1.0f, 1.0f);

	DirectX::XMFLOAT2 size = TEXTURE_LOADER->getTextureSize(mSpriteData->fileName);

	mPivot.x = (size.x / 2) * -aX;
	mPivot.y = (size.y / 2) * aY;
}

//-------------------------------------------------------------------------------------------------
/// 描画開始位置を設定する
/// @param aX 描画開始位置x(-1~1)
/// @param aY 描画開始位置y(-1~1)
void SpriteRenderer::setAnchor(float aX, float aY)
{
	aX = Math::Clamp(aX, -1.0f, 1.0f);
	aY = Math::Clamp(aY, -1.0f, 1.0f);

	mAnchor.x = aX;
	mAnchor.y = aY;
}

//-------------------------------------------------------------------------------------------------
/// UV分割数を設定する
/// @param aX 分割数x
/// @param aY 分割数y
void SpriteRenderer::setSplit(const UINT& aX, const UINT& aY)
{
	mSplit.x = (float)aX;
	mSplit.y = (float)aY;
}

} // namespace
// EOF
