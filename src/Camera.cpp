#include "Camera.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
Camera::Camera()
	: mFov(60)
	, mNearZ(0.3f)
	, mFarZ(1000)
{
	mTransform.pos = Vector3(0, 1, -10);
}

//-------------------------------------------------------------------------------------------------
void Camera::update()
{
	setUpTransform();
}

//-------------------------------------------------------------------------------------------------
void Camera::setUpTransform()
{
	// Viewマトリクス設定
	DirectX::XMVECTOR pos = { mTransform.pos.x, mTransform.pos.y, mTransform.pos.z, 0 };
	DirectX::XMVECTOR forcus = { mTransform.pos.x, mTransform.pos.y, mTransform.pos.z + 1, 0 };
	DirectX::XMVECTOR upVec = { 0, 1, 0, 0 };
	DirectX::XMMATRIX rot = DirectX::XMMatrixRotationRollPitchYaw(mTransform.rot.x, mTransform.rot.y, -mTransform.rot.z);
	DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixLookAtLH(pos, forcus, upVec) * rot;

	// ビューポート
	D3D11_VIEWPORT vp;
	UINT numVierports = 1;
	Direct3D11::getInst()->getContext()->RSGetViewports(&numVierports, &vp);

	// プロジェクションマトリクス設定
	DirectX::XMMATRIX projMatrix = DirectX::XMMatrixPerspectiveFovLH(
		DirectX::XMConvertToRadians(mFov),
		(float)vp.Width / (float)vp.Height,
		mNearZ,
		mFarZ
	);

	// コンスタントバッファを設定する
	XMStoreFloat4x4(&Direct3D11::getInst()->getConstantBufferData()->View, XMMatrixTranspose(viewMatrix));
	XMStoreFloat4x4(&Direct3D11::getInst()->getConstantBufferData()->Projection, XMMatrixTranspose(projMatrix));
}

//-------------------------------------------------------------------------------------------------
void Camera::draw()
{
}

} // namespace
// EOF
