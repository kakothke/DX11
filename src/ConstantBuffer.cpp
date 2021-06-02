#include "ConstantBuffer.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
ConstantBuffer::ConstantBuffer()
	: mBuffer()
	, mData()
{
	mBuffer.clear();
}

//-------------------------------------------------------------------------------------------------
ConstantBuffer::~ConstantBuffer()
{
	for (auto buffer : mBuffer) {
		if (buffer.second) {
			buffer.second->Release();
			buffer.second = nullptr;
		}
	}
	mBuffer.clear();
}

//-------------------------------------------------------------------------------------------------
bool ConstantBuffer::create()
{
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	// 変換行列
	bufferDesc.ByteWidth = sizeof(CB_MATRIX);
	if (FAILED(Direct3D11::getInst()->getDevice()->CreateBuffer(&bufferDesc, nullptr, &mBuffer[MATRIX]))) {
		return false;
	}
	// 変換行列2D
	bufferDesc.ByteWidth = sizeof(CB_SPRITE);
	if (FAILED(Direct3D11::getInst()->getDevice()->CreateBuffer(&bufferDesc, nullptr, &mBuffer[SPRITE]))) {
		return false;
	}
	// カメラ情報
	bufferDesc.ByteWidth = sizeof(CB_CAMERA);
	if (FAILED(Direct3D11::getInst()->getDevice()->CreateBuffer(&bufferDesc, nullptr, &mBuffer[CAMERA]))) {
		return false;
	}
	// ディレクショナルライト情報
	bufferDesc.ByteWidth = sizeof(CB_DLIGHT);
	if (FAILED(Direct3D11::getInst()->getDevice()->CreateBuffer(&bufferDesc, nullptr, &mBuffer[DLIGHT]))) {
		return false;
	}
	// マテリアル情報
	bufferDesc.ByteWidth = sizeof(CB_MATERIAL);
	if (FAILED(Direct3D11::getInst()->getDevice()->CreateBuffer(&bufferDesc, nullptr, &mBuffer[MATERIAL]))) {
		return false;
	}

	// スプライト用プロジェクション行列をセット
	float w = Define::ResolutionWidth;
	float h = Define::ResolutionHeight;
	DirectX::XMMATRIX proj2D = {
	2 / w , 0     , 0, 0,
	0     , 2 / h , 0, 0,
	0     , 0     , 1, 0,
	0     , 0     , 0, 1
	};
	XMStoreFloat4x4(&mData.SPRITE.PROJ_2D, XMMatrixTranspose(proj2D));
	updateSprite();

	return true;
}

//-------------------------------------------------------------------------------------------------
/// Worldマトリクス設定
void ConstantBuffer::setMatrixW(const DirectX::XMFLOAT3X3& aTransform)
{
	DirectX::XMMATRIX pos = DirectX::XMMatrixTranslation(
		aTransform._11,
		aTransform._12,
		aTransform._13
	);
	DirectX::XMMATRIX rot = DirectX::XMMatrixRotationRollPitchYaw(
		aTransform._21,
		aTransform._22,
		aTransform._23
	);
	DirectX::XMMATRIX scale = DirectX::XMMatrixScaling(
		aTransform._31,
		aTransform._32,
		aTransform._33
	);
	DirectX::XMMATRIX worldMatrix = scale * rot * pos;
	XMStoreFloat4x4(&mData.MATRIX.W, XMMatrixTranspose(worldMatrix));
}

//-------------------------------------------------------------------------------------------------
/// Viewマトリクス設定
void ConstantBuffer::setMatrixV(const DirectX::XMFLOAT3X3& aTransform)
{
	DirectX::XMVECTOR pos = {
		aTransform._11,
		aTransform._12,
		aTransform._13
	};
	DirectX::XMVECTOR forcus = {
		aTransform._11,
		aTransform._12,
		aTransform._13 + 1
	};
	DirectX::XMVECTOR upVec = {
		0,
		1,
		0
	};
	DirectX::XMMATRIX rot = DirectX::XMMatrixRotationRollPitchYaw(
		aTransform._21,
		aTransform._22,
		-aTransform._23
	);
	DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixLookAtLH(pos, forcus, upVec) * rot;
	XMStoreFloat4x4(&mData.MATRIX.V, XMMatrixTranspose(viewMatrix));
}

//-------------------------------------------------------------------------------------------------
/// Projectionマトリクス設定
void ConstantBuffer::setMatrixP(const float aFov, const float aNearZ, const float aFarZ)
{
	D3D11_VIEWPORT vp;
	UINT numVierports = 1;
	Direct3D11::getInst()->getContext()->RSGetViewports(&numVierports, &vp);
	DirectX::XMMATRIX projMatrix = DirectX::XMMatrixPerspectiveFovLH(
		DirectX::XMConvertToRadians(aFov),
		(float)vp.Width / (float)vp.Height,
		aNearZ,
		aFarZ
	);

	XMStoreFloat4x4(&mData.MATRIX.P, XMMatrixTranspose(projMatrix));
}
//-------------------------------------------------------------------------------------------------
/// マトリクスコンスタントバッファを更新する
void ConstantBuffer::updateMatrix()
{
	Direct3D11::getInst()->getContext()->UpdateSubresource(
		mBuffer[MATRIX],
		0,
		NULL,
		&mData.MATRIX,
		0,
		0
	);
	Direct3D11::getInst()->getContext()->VSSetConstantBuffers(MATRIX, 1, &mBuffer[MATRIX]);
	Direct3D11::getInst()->getContext()->PSSetConstantBuffers(MATRIX, 1, &mBuffer[MATRIX]);
}

//-------------------------------------------------------------------------------------------------
void ConstantBuffer::updateSprite()
{
	Direct3D11::getInst()->getContext()->UpdateSubresource(
		mBuffer[SPRITE],
		0,
		NULL,
		&mData.SPRITE,
		0,
		0
	);
	Direct3D11::getInst()->getContext()->VSSetConstantBuffers(SPRITE, 1, &mBuffer[SPRITE]);
	Direct3D11::getInst()->getContext()->PSSetConstantBuffers(SPRITE, 1, &mBuffer[SPRITE]);
}

//-------------------------------------------------------------------------------------------------
/// カメラコンスタントバッファを更新する
void ConstantBuffer::updateCamera(const DirectX::XMVECTOR& aPos, const DirectX::XMVECTOR& aRot)
{
	XMStoreFloat4(&mData.CAMERA.POS, aPos);
	XMStoreFloat4(&mData.CAMERA.ROT, aRot);

	// 更新
	Direct3D11::getInst()->getContext()->UpdateSubresource(
		mBuffer[CAMERA],
		0,
		NULL,
		&mData.CAMERA,
		0,
		0
	);
	Direct3D11::getInst()->getContext()->VSSetConstantBuffers(CAMERA, 1, &mBuffer[CAMERA]);
	Direct3D11::getInst()->getContext()->PSSetConstantBuffers(CAMERA, 1, &mBuffer[CAMERA]);
}

//-------------------------------------------------------------------------------------------------
/// ディレクショナルライトを更新する
void ConstantBuffer::updateDLight(const DirectX::XMVECTOR& aRot, const DirectX::XMFLOAT4& aCol)
{
	XMStoreFloat4(&mData.DLIGHT.ROT, aRot);
	mData.DLIGHT.COL = aCol;

	// 更新
	Direct3D11::getInst()->getContext()->UpdateSubresource(
		mBuffer[DLIGHT],
		0,
		NULL,
		&mData.DLIGHT,
		0,
		0
	);
	Direct3D11::getInst()->getContext()->VSSetConstantBuffers(DLIGHT, 1, &mBuffer[DLIGHT]);
	Direct3D11::getInst()->getContext()->PSSetConstantBuffers(DLIGHT, 1, &mBuffer[DLIGHT]);
}

//-------------------------------------------------------------------------------------------------
/// マテリアルコンスタントバッファを更新する
void ConstantBuffer::updateMaterial(const OBJMaterial& aMaterial)
{
	// アンビエント
	mData.MATERIAL.A = DirectX::XMFLOAT4(
		aMaterial.ambient[0],
		aMaterial.ambient[1],
		aMaterial.ambient[2],
		1
	);

	// ディフューズ
	mData.MATERIAL.D = DirectX::XMFLOAT4(
		aMaterial.diffuse[0],
		aMaterial.diffuse[1],
		aMaterial.diffuse[2],
		1
	);

	// スペキュラー
	mData.MATERIAL.S = DirectX::XMFLOAT4(
		aMaterial.specular[0],
		aMaterial.specular[1],
		aMaterial.specular[2],
		1
	);

	// 更新
	Direct3D11::getInst()->getContext()->UpdateSubresource(
		mBuffer[MATERIAL],
		0,
		NULL,
		&mData.MATERIAL,
		0,
		0
	);
	Direct3D11::getInst()->getContext()->VSSetConstantBuffers(MATERIAL, 1, &mBuffer[MATERIAL]);
	Direct3D11::getInst()->getContext()->PSSetConstantBuffers(MATERIAL, 1, &mBuffer[MATERIAL]);
}

} // namespace
// EOF
