#include "SpriteRenderer.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "ConstantBuffer.h"
#include "TextureLoader.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
SpriteRenderer::SpriteRenderer()
	: mSpriteData()
	, mShaderData()
{
}

//-------------------------------------------------------------------------------------------------
SpriteRenderer::~SpriteRenderer()
{
}

//-------------------------------------------------------------------------------------------------
bool SpriteRenderer::render(const Transform& aTransform)
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
	ConstantBuffer::getInst()->setMatrixW(aTransform);
	ConstantBuffer::getInst()->updateMatrix();

	// テクスチャーセット
	Direct3D11::getInst()->setTexture(TextureLoader::getInst()->getTexture(mSpriteData->fileName));

	// 描画
	Direct3D11::getInst()->getContext()->Draw(4, 0);

	return true;
}

//-------------------------------------------------------------------------------------------------
void SpriteRenderer::setSpriteAndShaderData(const char* aSpriteFileName, const char* aShaderFileName)
{
	mSpriteData = SpriteLoader::getInst()->getSpriteData(aSpriteFileName);
	mShaderData = ShaderLoader::getInst()->getShaderData(aShaderFileName);
}

} // namespace
// EOF
