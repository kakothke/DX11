#include "ObjRenderer.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
ObjRenderer::ObjRenderer()
	: mObjData()
	, mShaderData()
{
}

//-------------------------------------------------------------------------------------------------
ObjRenderer::~ObjRenderer()
{
}

//-------------------------------------------------------------------------------------------------
bool ObjRenderer::render(const Transform& aTransform)
{
	// 読み込みチェック
	if (!mObjData || !mShaderData) {
		return false;
	}

	// シェーダーの指定
	Direct3D11::getInst()->setUpContext(mShaderData);

	// IAに設定する頂点バッファの指定
	int count = 0;
	UINT strides = sizeof(ObjVertexData);
	UINT offsets = 0;
	Direct3D11::getInst()->getContext()->IASetVertexBuffers(
		0,
		1,
		&mObjData->vertexBuffer,
		&strides,
		&offsets
	);
	Direct3D11::getInst()->getContext()->IASetIndexBuffer(
		mObjData->indexBuffer,
		DXGI_FORMAT_R16_UINT,
		0
	);

	// ワールドマトリクス設定
	DirectX::XMMATRIX worldMatrix;
	DirectX::XMMATRIX pos = DirectX::XMMatrixTranslation(aTransform.pos.x, aTransform.pos.y, aTransform.pos.z);
	DirectX::XMMATRIX rot = DirectX::XMMatrixRotationRollPitchYaw(aTransform.rot.x, aTransform.rot.y, aTransform.rot.z);
	DirectX::XMMATRIX scale = DirectX::XMMatrixScaling(aTransform.scale.x, aTransform.scale.y, aTransform.scale.z);
	worldMatrix = scale * rot * pos;

	// ワールドマトリクスをコンスタントバッファに設定
	XMStoreFloat4x4(&Direct3D11::getInst()->getConstantBufferData()->World, XMMatrixTranspose(worldMatrix));

	// コンスタントバッファ更新
	Direct3D11::getInst()->getContext()->UpdateSubresource(
		Direct3D11::getInst()->getConstantBuffer(),
		0,
		NULL,
		Direct3D11::getInst()->getConstantBufferData(),
		0,
		0
	);

	// コンテキストにコンスタントバッファを設定
	ID3D11Buffer* constantBuffer = Direct3D11::getInst()->getConstantBuffer();
	Direct3D11::getInst()->getContext()->VSSetConstantBuffers(0, 1, &constantBuffer);

	// 描画
	Direct3D11::getInst()->getContext()->DrawIndexed(mObjData->indexes.size(), 0, 0);

	return true;
}

//-------------------------------------------------------------------------------------------------
void ObjRenderer::setObjAndShaderData(const ObjList& aObjList, const ShaderList& aShaderList)
{
	mObjData = ObjLoader::getInst()->getObjData(aObjList);
	mShaderData = ShaderLoader::getInst()->getShaderData(aShaderList);
}

} // namespace
// EOF
