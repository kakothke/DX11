#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

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

	// プリミティブの形状を指定
	Direct3D11::getInst()->getContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// シェーダーの指定
	Direct3D11::getInst()->setUpContext(mShaderData);

	int cnt = 0;
	UINT strides = sizeof(OBJVertex);
	UINT offsets = 0;

	for (auto index : mOBJData->indexes) {
		// IAに設定する頂点バッファの指定
		Direct3D11::getInst()->getContext()->IASetVertexBuffers(
			0,
			1,
			&mOBJData->vertexBuffer,
			&strides,
			&offsets
		);
		Direct3D11::getInst()->getContext()->IASetIndexBuffer(
			mOBJData->indexBuffers[cnt],
			DXGI_FORMAT_R32_UINT,
			0
		);

		// コンスタントバッファを更新
		Direct3D11::getInst()->getConstantBuffer()->setMatrixW(aTransform);
		Direct3D11::getInst()->getConstantBuffer()->updateMatrix();
		Direct3D11::getInst()->getConstantBuffer()->updateMaterial(mOBJData->materials[index.first]);

		if (!mOBJData->materials[index.first].textureFileName.empty()) {
			// テクスチャーセット
			const char* texName = mOBJData->materials[index.first].textureFileName.c_str();
			Direct3D11::getInst()->setTexture(Resource::getInst()->Texture()->getTexture(texName));
		} else {
			Direct3D11::getInst()->setTexture(nullptr);
		}

		// 描画
		Direct3D11::getInst()->getContext()->DrawIndexed((UINT)index.second.size(), 0, 0);

		cnt++;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
void OBJRenderer::setObjAndShaderData(const char* aOBJFileName, const char* aShaderFileName)
{
	mOBJData = Resource::getInst()->OBJ()->getOBJData(aOBJFileName);
	mShaderData = Resource::getInst()->Shader()->getShaderData(aShaderFileName);
}

} // namespace
// EOF
