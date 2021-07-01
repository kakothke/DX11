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
void ConstantBuffer::setMatrixW(const Transform& aTransform)
{
	XMStoreFloat4x4(&mMATRIX.W, XMMatrixTranspose(aTransform.WorldMatrix()));
}

//-------------------------------------------------------------------------------------------------
/// ViewProjection行列設定
void ConstantBuffer::setMatrixV(const Transform& aTransform)
{
	// View
	Vector3 tmpPos = aTransform.pos + aTransform.rot * aTransform.localPos;
	Vector3 tmpForcus = tmpPos + Vector3::forward;
	Quaternion tmpRot = -aTransform.rot * -aTransform.localRot;
	DirectX::XMVECTOR pos = tmpPos.XMVECTOR();
	DirectX::XMVECTOR forcus = tmpForcus.XMVECTOR();
	DirectX::XMMATRIX rot = DirectX::XMMatrixRotationQuaternion(tmpRot.XMVECTOR());
	DirectX::XMVECTOR upVec = { 0.0f, 1.0f, 0.0f };
	DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixLookAtLH(pos, forcus, upVec) * rot;

	XMStoreFloat4x4(&mMATRIX.V, XMMatrixTranspose(viewMatrix));
}

//-------------------------------------------------------------------------------------------------
/// プロジェクション行列を設定する
/// @param aFov 
/// @param aNearZ 
/// @param aFarZ 
void ConstantBuffer::setMatrixP(const float& aFov, const float& aNearZ, const float& aFarZ)
{
	D3D11_VIEWPORT vp;
	UINT numVierports = 1;
	mContext->RSGetViewports(&numVierports, &vp);

	DirectX::XMMATRIX projMatrix = DirectX::XMMatrixPerspectiveFovLH(
		DirectX::XMConvertToRadians(aFov),
		vp.Width / vp.Height,
		aNearZ,
		aFarZ
	);

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
/// スプライトのワールド行列を設定する
/// @param aTransform トランスフォーム
/// @param aPivot 描画原点(-1~1, -1~1)
void ConstantBuffer::setSpriteMatrixW(const Transform& aTransform, const Vector2& aPivot)
{
	Vector2 split = Vector2((float)mSPRITE.SPLIT.x, (float)mSPRITE.SPLIT.y);

	DirectX::XMMATRIX pos = DirectX::XMMatrixTranslation(
		aTransform.pos.x, -aTransform.pos.y, aTransform.pos.z
	);
	DirectX::XMMATRIX rot = DirectX::XMMatrixRotationQuaternion(
		aTransform.rot.XMVECTOR()
	);
	DirectX::XMMATRIX scale = DirectX::XMMatrixScaling(
		aTransform.scale.x / split.x, aTransform.scale.y / split.y, 0.0f
	);
	DirectX::XMMATRIX pivot = DirectX::XMMatrixTranslation(
		aPivot.x * (aTransform.scale.x / split.x), aPivot.y * (aTransform.scale.y / split.y), 1.0f
	);
	DirectX::XMMATRIX worldMatrix = scale * rot * pos * pivot;

	XMStoreFloat4x4(&mSPRITE.MATRIX_W, XMMatrixTranspose(worldMatrix));
}

//-------------------------------------------------------------------------------------------------
/// スプライトのプロジェクション行列を作成する
/// @param aAnchor 描画開始位置(-1~1, -1~1)
void ConstantBuffer::setSpriteMatrixP(const Vector2& aAnchor)
{
	DirectX::XMMATRIX anchor = DirectX::XMMatrixIdentity();
	anchor.r[3].m128_f32[0] = aAnchor.x;
	anchor.r[3].m128_f32[1] = -aAnchor.y;

	const static auto width = Window::getInst()->windowWidth();
	const static auto height = Window::getInst()->windowHeight();
	DirectX::XMMATRIX proj2D = DirectX::XMMatrixIdentity();
	proj2D.r[0].m128_f32[0] = 2.0f / width;
	proj2D.r[1].m128_f32[1] = 2.0f / height;
	DirectX::XMMATRIX projMatrix = proj2D * anchor;

	XMStoreFloat4x4(&mSPRITE.MATRIX_P, XMMatrixTranspose(projMatrix));
}

//-------------------------------------------------------------------------------------------------
void ConstantBuffer::setSpriteSplit(const Vector2& aSplit)
{
	mSPRITE.SPLIT = DirectX::XMINT4((int32_t)aSplit.x, (int32_t)aSplit.y, 0, 0);
}

//-------------------------------------------------------------------------------------------------
///	スプライト情報を更新する
void ConstantBuffer::updateSprite()
{
	mContext->UpdateSubresource(mBuffers[SPRITE], 0, NULL, &mSPRITE, 0, 0);
	mContext->VSSetConstantBuffers(SPRITE, 1, &mBuffers[SPRITE]);
	mContext->PSSetConstantBuffers(SPRITE, 1, &mBuffers[SPRITE]);
}

//-------------------------------------------------------------------------------------------------
/// カメラ情報を更新する
void ConstantBuffer::updateCamera(const Vector3& aPos)
{
	mCAMERA.POS = aPos.XMFLOAT4();

	// 更新
	mContext->UpdateSubresource(mBuffers[CAMERA], 0, NULL, &mCAMERA, 0, 0);
	mContext->VSSetConstantBuffers(CAMERA, 1, &mBuffers[CAMERA]);
	mContext->PSSetConstantBuffers(CAMERA, 1, &mBuffers[CAMERA]);
}

//-------------------------------------------------------------------------------------------------
/// ディレクショナルライト情報を更新する
void ConstantBuffer::updateDLight(const Vector3& aAngle, const Color& aCol)
{
	Vector3 angle(-aAngle.y, aAngle.x, 0.0f);
	mDLIGHT.ANGLE = angle.Normalized().XMFLOAT4();
	mDLIGHT.COL = aCol.XMFLOAT4();

	// 更新
	mContext->UpdateSubresource(mBuffers[DLIGHT], 0, NULL, &mDLIGHT, 0, 0);
	mContext->VSSetConstantBuffers(DLIGHT, 1, &mBuffers[DLIGHT]);
	mContext->PSSetConstantBuffers(DLIGHT, 1, &mBuffers[DLIGHT]);
}

//-------------------------------------------------------------------------------------------------
/// カラー情報を更新する
void ConstantBuffer::updateColor(const Color& aCol0, const Color& aCol1)
{
	mCOLOR.COL0 = aCol0.XMFLOAT4();
	mCOLOR.COL1 = aCol1.XMFLOAT4();

	// 更新
	mContext->UpdateSubresource(mBuffers[COLOR], 0, NULL, &mCOLOR, 0, 0);
	mContext->VSSetConstantBuffers(COLOR, 1, &mBuffers[COLOR]);
	mContext->PSSetConstantBuffers(COLOR, 1, &mBuffers[COLOR]);
}

//-------------------------------------------------------------------------------------------------
/// マテリアル情報を更新する
void ConstantBuffer::updateMaterial(const OBJLoader::OBJMaterial& aMaterial)
{
	// アンビエント
	mMATERIAL.A = DirectX::XMFLOAT4(
		aMaterial.ambient[0], aMaterial.ambient[1], aMaterial.ambient[2], 1.0f
	);
	// ディフューズ
	mMATERIAL.D = DirectX::XMFLOAT4(
		aMaterial.diffuse[0], aMaterial.diffuse[1], aMaterial.diffuse[2], 1.0f
	);
	// スペキュラー
	mMATERIAL.S = DirectX::XMFLOAT4(
		aMaterial.specular[0], aMaterial.specular[1], aMaterial.specular[2], 1.0f
	);

	// 更新
	mContext->UpdateSubresource(mBuffers[MATERIAL], 0, NULL, &mMATERIAL, 0, 0);
	mContext->VSSetConstantBuffers(MATERIAL, 1, &mBuffers[MATERIAL]);
	mContext->PSSetConstantBuffers(MATERIAL, 1, &mBuffers[MATERIAL]);
}

} // namespace
// EOF
