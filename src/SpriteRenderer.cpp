#include "SpriteRenderer.h"

//-------------------------------------------------------------------------------------------------
#include "Math.h"
#include "TextureLoader.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
SpriteRenderer::SpriteRenderer()
	: mSpriteData()
	, mShaderData()
	, mColor(255, 255, 255, 255)
	, mPivot(0.5f, 0.5f)
	, mAnchor(0, 0)
	, mSplit(1, 1)
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

	// Direct3D11取得
	const static auto d3D11 = Direct3D11::getInst();
	const static auto context = d3D11->getContext();
	const static auto constantBuffer = d3D11->getConstantBuffer();

	// プリミティブの形状を指定
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// シェーダーの指定
	d3D11->setShader(mShaderData);

	UINT strides = sizeof(SpriteLoader::SpriteVertex);
	UINT offsets = 0;

	// IAに設定する頂点バッファの指定
	context->IASetVertexBuffers(0, 1, &mSpriteData->vertexBuffer, &strides, &offsets);

	// コンスタントバッファを更新
	constantBuffer->updateColor(mColor, mColor);
	constantBuffer->setSpriteSplit(mSplit);
	constantBuffer->setSpriteMatrixW(aTransform, mPivot);
	constantBuffer->updateSprite();

	// テクスチャーセット
	const static auto tex = TextureLoader::getInst();
	d3D11->setTexture(tex->getTexture(mSpriteData->fileName));

	// 描画
	context->Draw(4, 0);
}

//-------------------------------------------------------------------------------------------------
/// スプライトを設定する
/// @param aFileName ファイルパス
void SpriteRenderer::setSprite(const LPCSTR aFileName)
{
	const auto sprite = SpriteLoader::getInst()->getSpriteData(aFileName);
	mSpriteData = sprite;
}

//-------------------------------------------------------------------------------------------------
/// シェーダーを設定する
/// @param aFileName ファイルパス
void SpriteRenderer::setShader(const LPCSTR aFileName)
{
	const auto shader = ShaderLoader::getInst()->getShaderData(aFileName);
	mShaderData = shader;
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

	const auto tex = TextureLoader::getInst();
	DirectX::XMFLOAT2 size = tex->getTextureSize(mSpriteData->fileName);

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
