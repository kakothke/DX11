#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
#include "TextureLoader.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// シングルトンクラス
const static auto D3D11 = Direct3D11::getInst();
const static auto OBJ_LOADER = OBJLoader::getInst();
const static auto TEXTURE_LOADER = TextureLoader::getInst();
const static auto SHADER_LOADER = ShaderLoader::getInst();

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

	// プリミティブの形状を指定
	D3D11->getContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// シェーダーの指定
	D3D11->setShader(mShaderData);

	int cnt = 0;
	UINT strides = sizeof(OBJLoader::OBJVertex);
	UINT offsets = 0;

	for (const auto index : mOBJData->indexes) {
		// IAに設定する頂点バッファの指定
		D3D11->getContext()->IASetVertexBuffers(0, 1, &mOBJData->vertexBuffer, &strides, &offsets);
		D3D11->getContext()->IASetIndexBuffer(mOBJData->indexBuffers[cnt], DXGI_FORMAT_R32_UINT, 0);

		// コンスタントバッファを更新
		D3D11->getConstantBuffer()->setMatrixW(aTransform);
		D3D11->getConstantBuffer()->updateMatrix();
		D3D11->getConstantBuffer()->updateMaterial(mOBJData->materials[index.first]);

		if (!mOBJData->materials[index.first].textureFileName.empty()) {
			// テクスチャーセット
			const char* texName = mOBJData->materials[index.first].textureFileName.c_str();			
			D3D11->setTexture(TEXTURE_LOADER->getTexture(texName));
		} else {
			D3D11->setTexture(nullptr);
		}

		// 描画
		D3D11->getContext()->DrawIndexed((UINT)index.second.size(), 0, 0);

		cnt++;
	}
}

//-------------------------------------------------------------------------------------------------
/// OBJを設定する
/// @param aFileName ファイルパス
void OBJRenderer::setOBJ(const LPCSTR aFileName)
{
	mOBJData = OBJ_LOADER->getOBJData(aFileName);
}

//-------------------------------------------------------------------------------------------------
/// シェーダーを設定する
/// @param aFileName ファイルパス
void OBJRenderer::setShader(const LPCSTR aFileName)
{
	mShaderData = SHADER_LOADER->getShaderData(aFileName);
}

} // namespace
// EOF
