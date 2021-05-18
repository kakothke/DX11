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
bool OBJRenderer::render(const Transform& aTransform)
{
	// 読み込みチェック
	if (!mOBJData || !mShaderData) {
		return false;
	}

	// シェーダーの指定
	Direct3D11::getInst()->setUpContext(mShaderData);

	// IAに設定する頂点バッファの指定
	int count = 0;
	UINT strides = sizeof(OBJVertexData);
	UINT offsets = 0;
	Direct3D11::getInst()->getContext()->IASetVertexBuffers(
		0,
		1,
		&mOBJData->vertexBuffer,
		&strides,
		&offsets
	);
	Direct3D11::getInst()->getContext()->IASetIndexBuffer(
		mOBJData->indexBuffer,
		DXGI_FORMAT_R16_UINT,
		0
	);

	// ワールドマトリクス設定
	DirectX::XMMATRIX pos = DirectX::XMMatrixTranslation(aTransform.pos.x, aTransform.pos.y, aTransform.pos.z);
	DirectX::XMMATRIX rot = DirectX::XMMatrixRotationRollPitchYaw(aTransform.rot.x, aTransform.rot.y, aTransform.rot.z);
	DirectX::XMMATRIX scale = DirectX::XMMatrixScaling(aTransform.scale.x, aTransform.scale.y, aTransform.scale.z);
	DirectX::XMMATRIX worldMatrix = scale * rot * pos;

	// ワールドマトリクスをコンスタントバッファに設定
	XMStoreFloat4x4(&Direct3D11::getInst()->getConstantBufferData()->World, XMMatrixTranspose(worldMatrix));

	// コンスタントバッファを更新
	Direct3D11::getInst()->updateConstantBuffer();

	// 描画
	Direct3D11::getInst()->getContext()->DrawIndexed(mOBJData->indexes.size(), 0, 0);

	return true;
}

//-------------------------------------------------------------------------------------------------
void OBJRenderer::setObjAndShaderData(const OBJList& aOBJList, const ShaderList& aShaderList)
{
	mOBJData = OBJLoader::getInst()->getObjData(aOBJList);
	mShaderData = ShaderLoader::getInst()->getShaderData(aShaderList);
}

} // namespace
// EOF
