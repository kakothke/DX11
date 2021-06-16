#include "SpriteRenderer.h"

//-------------------------------------------------------------------------------------------------
#include "TextureLoader.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
SpriteRenderer::SpriteRenderer()
	: mSpriteData()
	, mShaderData()
	, mColor(1, 1, 1, 1)
	, mPivot(0.5f, 0.5f)
	, mAnchor(-1, -1)
	, mSplit(1, 1)
{
}

//-------------------------------------------------------------------------------------------------
SpriteRenderer::~SpriteRenderer()
{
}

//-------------------------------------------------------------------------------------------------
bool SpriteRenderer::render(const DirectX::XMFLOAT3X3& aTransform)
{
	// 読み込みチェック
	if (!mSpriteData || !mShaderData) {
		return false;
	}

	// Direct3D11取得
	static auto d3d11 = Direct3D11::getInst();
	static auto context = d3d11->getContext();
	static auto constantBuf = d3d11->getConstantBuffer();

	// プリミティブの形状を指定
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// シェーダーの指定
	d3d11->setUpContext(mShaderData);

	int cnt = 0;
	UINT strides = sizeof(SpriteVertex);
	UINT offsets = 0;

	// IAに設定する頂点バッファの指定
	context->IASetVertexBuffers(0, 1, &mSpriteData->vertexBuffer, &strides, &offsets);

	// コンスタントバッファを更新
	constantBuf->updateColor(mColor, mColor);
	constantBuf->updateSprite(aTransform, mAnchor, mPivot, mSplit);

	// テクスチャーセット
	static auto texture = TextureLoader::getInst();
	d3d11->setTexture(texture->getTexture(mSpriteData->fileName));

	// 描画
	context->Draw(4, 0);

	return true;
}

//-------------------------------------------------------------------------------------------------
void SpriteRenderer::setSpriteAndShaderData(const char* aSpriteFileName, const char* aShaderFileName)
{
	auto sprite = SpriteLoader::getInst()->getSpriteData(aSpriteFileName);
	mSpriteData = sprite;
	auto shader = ShaderLoader::getInst()->getShaderData(aShaderFileName);
	mShaderData = shader;
}

//-------------------------------------------------------------------------------------------------
void SpriteRenderer::setColor(const DirectX::XMFLOAT4& aColor)
{
	mColor = aColor;
}

//-------------------------------------------------------------------------------------------------
void SpriteRenderer::setPivot(const DirectX::XMFLOAT2& aPivot)
{
	mPivot = aPivot;
}

//-------------------------------------------------------------------------------------------------
void SpriteRenderer::setAnchor(const DirectX::XMFLOAT2& aAnchor)
{
	mAnchor = aAnchor;
}

//-------------------------------------------------------------------------------------------------
void SpriteRenderer::setSplit(const DirectX::XMINT2& aSplit)
{
	mSplit = aSplit;
}

} // namespace
// EOF
