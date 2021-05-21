#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "ConstantBuffer.h"

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
bool OBJRenderer::render(const Transform& aTransform)
{
	// 読み込みチェック
	if (!mOBJData || !mShaderData) {
		return false;
	}

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
		ConstantBuffer::getInst()->setMatrixW(aTransform);
		ConstantBuffer::getInst()->updateMatrix();
		ConstantBuffer::getInst()->updateMaterial(mOBJData->materials[index.first]);

		// 描画
		Direct3D11::getInst()->getContext()->DrawIndexed((UINT)index.second.size(), 0, 0);

		cnt++;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
void OBJRenderer::setObjAndShaderData(const char* aOBJFileName, const char* aShaderFileName)
{
	mOBJData = OBJLoader::getInst()->getObjData(aOBJFileName);
	mShaderData = ShaderLoader::getInst()->getShaderData(aShaderFileName);
}

} // namespace
// EOF
