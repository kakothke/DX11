#include "SpriteRenderer.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"

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

	// プリミティブの形状を指定
	Direct3D11::getInst()->getContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// シェーダーの指定
	Direct3D11::getInst()->setUpContext(mShaderData);

	int cnt = 0;
	UINT strides = sizeof(SpriteVertex);
	UINT offsets = 0;

	// IAに設定する頂点バッファの指定
	Direct3D11::getInst()->getContext()->IASetVertexBuffers(
		0,
		1,
		&mSpriteData->vertexBuffer,
		&strides,
		&offsets
	);

	// コンスタントバッファを更新
	Direct3D11::getInst()->getConstantBuffer()->updateColor(mColor, mColor);
	Direct3D11::getInst()->getConstantBuffer()->updateSprite(aTransform, mAnchor, mPivot, mSplit);

	// テクスチャーセット
	Direct3D11::getInst()->setTexture(Resource::getInst()->Texture()->getTexture(mSpriteData->fileName));

	// 描画
	Direct3D11::getInst()->getContext()->Draw(4, 0);

	return true;
}

//-------------------------------------------------------------------------------------------------
void SpriteRenderer::setSpriteAndShaderData(const char* aSpriteFileName, const char* aShaderFileName)
{
	mSpriteData = Resource::getInst()->Sprite()->getSpriteData(aSpriteFileName);
	mShaderData = Resource::getInst()->Shader()->getShaderData(aShaderFileName);
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
