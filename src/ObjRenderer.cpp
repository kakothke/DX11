#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
#include "TextureLoader.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
OBJRenderer::OBJRenderer()
	: mOBJData()
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

	// Direct3D11取得
	const static auto d3D11 = Direct3D11::getInst();
	const static auto context = d3D11->getContext();
	const static auto cBuf = d3D11->getConstantBuffer();

	// プリミティブの形状を指定
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// シェーダーの指定
	d3D11->setShader(mShaderData);

	int cnt = 0;
	UINT strides = sizeof(OBJVertex);
	UINT offsets = 0;

	for (auto index : mOBJData->indexes) {
		// IAに設定する頂点バッファの指定
		context->IASetVertexBuffers(0, 1, &mOBJData->vertexBuffer, &strides, &offsets);
		context->IASetIndexBuffer(mOBJData->indexBuffers[cnt], DXGI_FORMAT_R32_UINT, 0);

		// コンスタントバッファを更新
		cBuf->setMatrixW(aTransform);
		cBuf->updateMatrix();
		cBuf->updateMaterial(mOBJData->materials[index.first]);

		if (!mOBJData->materials[index.first].textureFileName.empty()) {
			// テクスチャーセット
			const char* texName = mOBJData->materials[index.first].textureFileName.c_str();
			const static auto tex = TextureLoader::getInst();
			d3D11->setTexture(tex->getTexture(texName));
		} else {
			d3D11->setTexture(nullptr);
		}

		// 描画
		context->DrawIndexed((UINT)index.second.size(), 0, 0);

		cnt++;
	}
}

//-------------------------------------------------------------------------------------------------
/// OBJとシェーダーを設定する
/// @param aOBJFileName OBJファイルパス
/// @param aShaderFileName シェーダーファイルパス
void OBJRenderer::setObjAndShaderData(const char* const aOBJFileName, const char* const aShaderFileName)
{
	const auto obj = OBJLoader::getInst()->getOBJData(aOBJFileName);
	mOBJData = obj;
	const auto shader = ShaderLoader::getInst()->getShaderData(aShaderFileName);
	mShaderData = shader;
}

} // namespace
// EOF
