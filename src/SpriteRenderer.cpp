#include "SpriteRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
SpriteRenderer::SpriteRenderer()
	: mD3D11(Direct3D11::getInst())
	, mTex(TextureLoader::getInst())
	, mSpriteData()
	, mShaderData()
	, mColor(1, 1, 1, 1)
	, mPivot(0.5f, 0.5f)
	, mAnchor(-1, -1)
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
void SpriteRenderer::render(const DirectX::XMFLOAT3X3& aTransform)
{
	// 読み込みチェック
	if (!mSpriteData || !mShaderData) {
		return;
	}

	// プリミティブの形状を指定
	mD3D11->getContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// シェーダーの指定
	mD3D11->setUpContext(mShaderData);

	int cnt = 0;
	UINT strides = sizeof(SpriteVertex);
	UINT offsets = 0;

	// IAに設定する頂点バッファの指定
	mD3D11->getContext()->IASetVertexBuffers(0, 1, &mSpriteData->vertexBuffer, &strides, &offsets);

	// コンスタントバッファを更新
	mD3D11->getConstantBuffer()->updateColor(mColor, mColor);
	mD3D11->getConstantBuffer()->updateSprite(aTransform, mAnchor, mPivot, mSplit);

	// テクスチャーセット
	mD3D11->setTexture(mTex->getTexture(mSpriteData->fileName));

	// 描画
	mD3D11->getContext()->Draw(4, 0);
}

//-------------------------------------------------------------------------------------------------
/// スプライトとシェーダーを設定する
/// @param aSpriteFileName スプライトのファイルパス
/// @param aShaderFileName シェーダーのファイルパス
void SpriteRenderer::setSpriteAndShaderData(const char* aSpriteFileName, const char* aShaderFileName)
{
	auto sprite = SpriteLoader::getInst()->getSpriteData(aSpriteFileName);
	mSpriteData = sprite;
	auto shader = ShaderLoader::getInst()->getShaderData(aShaderFileName);
	mShaderData = shader;
}

//-------------------------------------------------------------------------------------------------
/// カラーを設定する
/// @param aColor 色(0~1)
void SpriteRenderer::setColor(const DirectX::XMFLOAT4& aColor)
{
	mColor = aColor;
}

//-------------------------------------------------------------------------------------------------
/// 描画中心位置を設定する
/// @param aPivot 中心位置(x,y){0~1}
void SpriteRenderer::setPivot(const DirectX::XMFLOAT2& aPivot)
{
	mPivot = aPivot;
}

//-------------------------------------------------------------------------------------------------
/// 描画開始位置を設定する
/// @param aAnchor 開始位置(x,y){-1~1}
void SpriteRenderer::setAnchor(const DirectX::XMFLOAT2& aAnchor)
{
	mAnchor = aAnchor;
}

//-------------------------------------------------------------------------------------------------
/// UV分割数を設定する
/// @param aSplit 分割数(x,y)
void SpriteRenderer::setSplit(const DirectX::XMINT2& aSplit)
{
	mSplit = aSplit;
}

} // namespace
// EOF
