#include "SpriteRenderer.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "ResourceManager.h"

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
	/*Direct3D11::getInst()->getConstantBuffer()->setMatrixW(aTransform.pos.XMFLOAT3(), aTransform.rot.XMFLOAT3(), aTransform.scale.XMFLOAT3());
	Direct3D11::getInst()->getConstantBuffer()->updateMatrix();*/

	// テクスチャーセット
	Direct3D11::getInst()->setTexture(ResourceManager::getInst()->Texture()->getTexture(mSpriteData->fileName));

	// 描画
	Direct3D11::getInst()->getContext()->Draw(4, 0);

	return true;
}

//-------------------------------------------------------------------------------------------------
void SpriteRenderer::setSpriteAndShaderData(const char* aSpriteFileName, const char* aShaderFileName)
{
	mSpriteData = ResourceManager::getInst()->Sprite()->getSpriteData(aSpriteFileName);
	mShaderData = ResourceManager::getInst()->Shader()->getShaderData(aShaderFileName);
}

} // namespace
// EOF
