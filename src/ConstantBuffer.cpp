#include "ConstantBuffer.h"

//-------------------------------------------------------------------------------------------------
#include "Window.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
ConstantBuffer::ConstantBuffer()
	: mContext(nullptr)
	, mBuffers()
	, mMATRIX()
	, mSPRITE()
	, mCAMERA()
	, mDLIGHT()
	, mCOLOR()
	, mMATERIAL()
{
	mBuffers.clear();
}

//-------------------------------------------------------------------------------------------------
ConstantBuffer::~ConstantBuffer()
{
	for (auto buffer : mBuffers) {
		if (buffer.second) {
			buffer.second->Release();
			buffer.second = nullptr;
		}
	}
	mBuffers.clear();
}

//-------------------------------------------------------------------------------------------------
bool ConstantBuffer::initialize(ID3D11Device* aDevice, ID3D11DeviceContext* aContext)
{
	// コンテキストをリンク
	mContext = aContext;

	// コンスタントバッファ作成
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	HRESULT hr;
	// 変換行列
	bufferDesc.ByteWidth = sizeof(CB_MATRIX);
	hr = aDevice->CreateBuffer(&bufferDesc, nullptr, &mBuffers[MATRIX]);
	if (FAILED(hr)) {
		return false;
	}
	// 変換行列2D
	bufferDesc.ByteWidth = sizeof(CB_SPRITE);
	hr = aDevice->CreateBuffer(&bufferDesc, nullptr, &mBuffers[SPRITE]);
	if (FAILED(hr)) {
		return false;
	}
	// カメラ情報
	bufferDesc.ByteWidth = sizeof(CB_CAMERA);
	hr = aDevice->CreateBuffer(&bufferDesc, nullptr, &mBuffers[CAMERA]);
	if (FAILED(hr)) {
		return false;
	}
	// ディレクショナルライト情報
	bufferDesc.ByteWidth = sizeof(CB_DLIGHT);
	hr = aDevice->CreateBuffer(&bufferDesc, nullptr, &mBuffers[DLIGHT]);
	if (FAILED(hr)) {
		return false;
	}
	// カラー情報
	bufferDesc.ByteWidth = sizeof(CB_COLOR);
	hr = aDevice->CreateBuffer(&bufferDesc, nullptr, &mBuffers[COLOR]);
	if (FAILED(hr)) {
		return false;
	}
	// マテリアル情報
	bufferDesc.ByteWidth = sizeof(CB_MATERIAL);
	hr = aDevice->CreateBuffer(&bufferDesc, nullptr, &mBuffers[MATERIAL]);
	if (FAILED(hr)) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// World行列設定
void ConstantBuffer::setMatrixW(const DirectX::XMFLOAT3X3& aTransform)
{
	DirectX::XMMATRIX pos = DirectX::XMMatrixTranslation(
		aTransform._11, aTransform._12, aTransform._13
	);
	DirectX::XMMATRIX rot = DirectX::XMMatrixRotationRollPitchYaw(
		aTransform._21, aTransform._22, aTransform._23
	);
	DirectX::XMMATRIX scale = DirectX::XMMatrixScaling(
		aTransform._31, aTransform._32, aTransform._33
	);
	DirectX::XMMATRIX worldMatrix = scale * rot * pos;
	XMStoreFloat4x4(&mMATRIX.W, XMMatrixTranspose(worldMatrix));
}

//-------------------------------------------------------------------------------------------------
/// ViewProjection行列設定
void ConstantBuffer::setMatrixVP(const DirectX::XMFLOAT3X3& aTransform, const DirectX::XMFLOAT3& aCamera)
{
	// View
	DirectX::XMVECTOR pos = {
		aTransform._11,	aTransform._12,	aTransform._13
	};
	DirectX::XMVECTOR forcus = {
		aTransform._11,	aTransform._12,	aTransform._13 + 1
	};
	DirectX::XMMATRIX rot = DirectX::XMMatrixRotationRollPitchYaw(
		aTransform._21, aTransform._22, -aTransform._23
	);
	DirectX::XMVECTOR upVec = { 0, 1, 0 };
	DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixLookAtLH(pos, forcus, upVec) * rot;
	XMStoreFloat4x4(&mMATRIX.V, XMMatrixTranspose(viewMatrix));

	// Projection
	D3D11_VIEWPORT vp;
	UINT numVierports = 1;
	mContext->RSGetViewports(&numVierports, &vp);

	auto fov = DirectX::XMConvertToRadians(aCamera.x);
	auto nearZ = aCamera.y;
	auto farZ = aCamera.z;

	DirectX::XMMATRIX projMatrix;
	projMatrix = DirectX::XMMatrixPerspectiveFovLH(fov, vp.Width / vp.Height, nearZ, farZ);

	XMStoreFloat4x4(&mMATRIX.P, XMMatrixTranspose(projMatrix));
}
//-------------------------------------------------------------------------------------------------
/// 変換行列情報を更新する
void ConstantBuffer::updateMatrix()
{
	mContext->UpdateSubresource(mBuffers[MATRIX], 0, NULL, &mMATRIX, 0, 0);
	mContext->VSSetConstantBuffers(MATRIX, 1, &mBuffers[MATRIX]);
	mContext->PSSetConstantBuffers(MATRIX, 1, &mBuffers[MATRIX]);
}

//-------------------------------------------------------------------------------------------------
///	スプライト情報を更新する
void ConstantBuffer::updateSprite(
	const DirectX::XMFLOAT3X3& aTransform,
	const DirectX::XMFLOAT2& aAnchor,
	const DirectX::XMFLOAT2& aPivot,
	const DirectX::XMINT2 aSplit
)
{
	// World
	DirectX::XMMATRIX pos = DirectX::XMMatrixTranslation(
		aTransform._11, -aTransform._12, aTransform._13
	);
	DirectX::XMMATRIX rot = DirectX::XMMatrixRotationRollPitchYaw(
		aTransform._21, aTransform._22, aTransform._23
	);
	DirectX::XMMATRIX scale = DirectX::XMMatrixScaling(
		aTransform._31, aTransform._32, 0
	);
	DirectX::XMMATRIX worldMatrix = scale * rot * pos;
	XMStoreFloat4x4(&mSPRITE.MATRIX_W, XMMatrixTranspose(worldMatrix));

	// Projection
	DirectX::XMMATRIX anchor = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		aAnchor.x, -aAnchor.y, 0, 1
	};
	static auto width = Window::getInst()->windowWidth();
	static auto height = Window::getInst()->windowHeight();
	DirectX::XMMATRIX proj2D = {
		2.0f / width , 0, 0, 0,
		0, 2.0f / height, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	DirectX::XMMATRIX projMatrix = proj2D * anchor;
	XMStoreFloat4x4(&mSPRITE.MATRIX_P, XMMatrixTranspose(projMatrix));

	// Pivot
	mSPRITE.PIVOT = DirectX::XMFLOAT4(aPivot.x, aPivot.y, 0, 0);

	// Split
	mSPRITE.SPLIT = DirectX::XMINT4(aSplit.x, aSplit.y, 0, 0);

	// 更新
	mContext->UpdateSubresource(mBuffers[SPRITE], 0, NULL, &mSPRITE, 0, 0);
	mContext->VSSetConstantBuffers(SPRITE, 1, &mBuffers[SPRITE]);
	mContext->PSSetConstantBuffers(SPRITE, 1, &mBuffers[SPRITE]);
}

//-------------------------------------------------------------------------------------------------
/// カメラ情報を更新する
void ConstantBuffer::updateCamera(const DirectX::XMVECTOR& aPos, const DirectX::XMVECTOR& aRot)
{
	XMStoreFloat4(&mCAMERA.POS, aPos);
	XMStoreFloat4(&mCAMERA.ROT, aRot);

	// 更新
	mContext->UpdateSubresource(mBuffers[CAMERA], 0, NULL, &mCAMERA, 0, 0);
	mContext->VSSetConstantBuffers(CAMERA, 1, &mBuffers[CAMERA]);
	mContext->PSSetConstantBuffers(CAMERA, 1, &mBuffers[CAMERA]);
}

//-------------------------------------------------------------------------------------------------
/// ディレクショナルライト情報を更新する
void ConstantBuffer::updateDLight(const DirectX::XMVECTOR& aRot, const DirectX::XMFLOAT4& aCol)
{
	XMStoreFloat4(&mDLIGHT.ROT, aRot);
	mDLIGHT.COL = aCol;

	// 更新
	mContext->UpdateSubresource(mBuffers[DLIGHT], 0, NULL, &mDLIGHT, 0, 0);
	mContext->VSSetConstantBuffers(DLIGHT, 1, &mBuffers[DLIGHT]);
	mContext->PSSetConstantBuffers(DLIGHT, 1, &mBuffers[DLIGHT]);
}

//-------------------------------------------------------------------------------------------------
/// カラー情報を更新する
void ConstantBuffer::updateColor(const DirectX::XMFLOAT4& aCol0, const DirectX::XMFLOAT4& aCol1)
{
	mCOLOR.COL0 = aCol0;
	mCOLOR.COL1 = aCol1;

	// 更新
	mContext->UpdateSubresource(mBuffers[COLOR], 0, NULL, &mCOLOR, 0, 0);
	mContext->VSSetConstantBuffers(COLOR, 1, &mBuffers[COLOR]);
	mContext->PSSetConstantBuffers(COLOR, 1, &mBuffers[COLOR]);
}

//-------------------------------------------------------------------------------------------------
/// マテリアル情報を更新する
void ConstantBuffer::updateMaterial(const OBJMaterial& aMaterial)
{
	// アンビエント
	mMATERIAL.A = DirectX::XMFLOAT4(
		aMaterial.ambient[0], aMaterial.ambient[1], aMaterial.ambient[2], 1
	);
	// ディフューズ
	mMATERIAL.D = DirectX::XMFLOAT4(
		aMaterial.diffuse[0], aMaterial.diffuse[1], aMaterial.diffuse[2], 1
	);
	// スペキュラー
	mMATERIAL.S = DirectX::XMFLOAT4(
		aMaterial.specular[0], aMaterial.specular[1], aMaterial.specular[2], 1
	);

	// 更新
	mContext->UpdateSubresource(mBuffers[MATERIAL], 0, NULL, &mMATERIAL, 0, 0);
	mContext->VSSetConstantBuffers(MATERIAL, 1, &mBuffers[MATERIAL]);
	mContext->PSSetConstantBuffers(MATERIAL, 1, &mBuffers[MATERIAL]);
}

} // namespace
// EOF
