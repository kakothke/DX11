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
void OBJRenderer::render(const Transform& aTransform)
{
	// 読み込みチェック
	if (!mOBJData || !mShaderData) {
		return;
	}

	// Direct3D11取得
	const static auto d3D11 = Direct3D11::getInst();
	const static auto context = d3D11->getContext();
	const static auto constantBuffer = d3D11->getConstantBuffer();

	// プリミティブの形状を指定
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// シェーダーの指定
	d3D11->setShader(mShaderData);

	int cnt = 0;
	UINT strides = sizeof(OBJLoader::OBJVertex);
	UINT offsets = 0;

	for (auto index : mOBJData->indexes) {
		// IAに設定する頂点バッファの指定
		context->IASetVertexBuffers(0, 1, &mOBJData->vertexBuffer, &strides, &offsets);
		context->IASetIndexBuffer(mOBJData->indexBuffers[cnt], DXGI_FORMAT_R32_UINT, 0);

		// コンスタントバッファを更新
		constantBuffer->setMatrixW(aTransform);
		constantBuffer->updateMatrix();
		constantBuffer->updateMaterial(mOBJData->materials[index.first]);

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
/// OBJを設定する
/// @param aFileName ファイルパス
void OBJRenderer::setOBJ(const LPCSTR aFileName)
{
	const auto obj = OBJLoader::getInst()->getOBJData(aFileName);
	mOBJData = obj;
}

//-------------------------------------------------------------------------------------------------
/// シェーダーを設定する
/// @param aFileName ファイルパス
void OBJRenderer::setShader(const LPCSTR aFileName)
{
	const auto shader = ShaderLoader::getInst()->getShaderData(aFileName);
	mShaderData = shader;
}

} // namespace
// EOF
