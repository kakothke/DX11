#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
OBJRenderer::OBJRenderer()
	: mD3D11(Direct3D11::getInst())
	, mTex(TextureLoader::getInst())
	, mOBJData()
	, mShaderData()
{
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
OBJRenderer::~OBJRenderer()
{
}

//-------------------------------------------------------------------------------------------------
/// 描画
/// @param aTransform トランスフォーム
void OBJRenderer::render(const DirectX::XMFLOAT3X3& aTransform)
{
	// 読み込みチェック
	if (!mOBJData || !mShaderData) {
		return;
	}

	// プリミティブの形状を指定
	mD3D11->getContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// シェーダーの指定
	mD3D11->setUpContext(mShaderData);

	int cnt = 0;
	UINT strides = sizeof(OBJVertex);
	UINT offsets = 0;

	for (auto index : mOBJData->indexes) {
		// IAに設定する頂点バッファの指定
		mD3D11->getContext()->IASetVertexBuffers(0, 1, &mOBJData->vertexBuffer, &strides, &offsets);
		mD3D11->getContext()->IASetIndexBuffer(mOBJData->indexBuffers[cnt], DXGI_FORMAT_R32_UINT, 0);

		// コンスタントバッファを更新
		mD3D11->getConstantBuffer()->setMatrixW(aTransform);
		mD3D11->getConstantBuffer()->updateMatrix();
		mD3D11->getConstantBuffer()->updateMaterial(mOBJData->materials[index.first]);

		if (!mOBJData->materials[index.first].textureFileName.empty()) {
			// テクスチャーセット
			const char* texName = mOBJData->materials[index.first].textureFileName.c_str();
			mD3D11->setTexture(mTex->getTexture(texName));
		} else {
			mD3D11->setTexture(nullptr);
		}

		// 描画
		mD3D11->getContext()->DrawIndexed((UINT)index.second.size(), 0, 0);

		cnt++;
	}
}

//-------------------------------------------------------------------------------------------------
/// OBJとシェーダーを設定する
/// @param aOBJFileName OBJファイルパス
/// @param aShaderFileName シェーダーファイルパス
void OBJRenderer::setObjAndShaderData(const char* aOBJFileName, const char* aShaderFileName)
{
	auto obj = OBJLoader::getInst()->getOBJData(aOBJFileName);
	mOBJData = obj;
	auto shader = ShaderLoader::getInst()->getShaderData(aShaderFileName);
	mShaderData = shader;
}

} // namespace
// EOF
