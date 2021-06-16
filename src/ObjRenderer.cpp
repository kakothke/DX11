#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
#include "TextureLoader.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
OBJRenderer::OBJRenderer()
	: mOBJData()
	, mShaderData()
{
}

//-------------------------------------------------------------------------------------------------
OBJRenderer::~OBJRenderer()
{
}

//-------------------------------------------------------------------------------------------------
bool OBJRenderer::render(const DirectX::XMFLOAT3X3& aTransform)
{
	// 読み込みチェック
	if (!mOBJData || !mShaderData) {
		return false;
	}

	// Direct3D11取得
	static auto d3d11 = Direct3D11::getInst();
	static auto context = d3d11->getContext();
	static auto constantBuf = d3d11->getConstantBuffer();

	// プリミティブの形状を指定
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// シェーダーの指定
	d3d11->setUpContext(mShaderData);

	int cnt = 0;
	UINT strides = sizeof(OBJVertex);
	UINT offsets = 0;

	for (auto index : mOBJData->indexes) {
		// IAに設定する頂点バッファの指定
		context->IASetVertexBuffers(0, 1, &mOBJData->vertexBuffer, &strides, &offsets);
		context->IASetIndexBuffer(mOBJData->indexBuffers[cnt], DXGI_FORMAT_R32_UINT, 0);

		// コンスタントバッファを更新
		constantBuf->setMatrixW(aTransform);
		constantBuf->updateMatrix();
		constantBuf->updateMaterial(mOBJData->materials[index.first]);

		if (!mOBJData->materials[index.first].textureFileName.empty()) {
			// テクスチャーセット
			const char* texName = mOBJData->materials[index.first].textureFileName.c_str();
			static auto texture = TextureLoader::getInst();
			d3d11->setTexture(texture->getTexture(texName));
		} else {
			d3d11->setTexture(nullptr);
		}

		// 描画
		context->DrawIndexed((UINT)index.second.size(), 0, 0);

		cnt++;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
void OBJRenderer::setObjAndShaderData(const char* aOBJFileName, const char* aShaderFileName)
{
	auto obj = OBJLoader::getInst()->getOBJData(aOBJFileName);
	mOBJData = obj;
	auto shader = ShaderLoader::getInst()->getShaderData(aShaderFileName);
	mShaderData = shader;
}

} // namespace
// EOF
