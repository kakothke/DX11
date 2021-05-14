#include "Camera.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
Camera::Camera()
	: mView()
	, mWorld()
{
}

//-------------------------------------------------------------------------------------------------
Camera::Camera(ViewMatrix aView)
	: mView(aView)
	, mWorld()
{
}

//-------------------------------------------------------------------------------------------------
Camera::Camera(WorldMatrix aWorld)
	: mView()
	, mWorld(aWorld)
{
}

//-------------------------------------------------------------------------------------------------
Camera::Camera(ViewMatrix aView, WorldMatrix aWorld)
	: mView(aView)
	, mWorld(aWorld)
{
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
	DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixLookAtLH(
		DirectX::XMVectorSet(mView.pos.x, mView.pos.y, mView.pos.z, 0),
		DirectX::XMVectorSet(mView.forcus.x, mView.forcus.y, mView.forcus.z, 0),
		DirectX::XMVectorSet(mView.up.x, mView.up.y, mView.up.z, 0)
	);

	// ビューポート
	D3D11_VIEWPORT vp;
	UINT pNumVierports = 1;
	Direct3D11::getInst()->getContext()->RSGetViewports(&pNumVierports, &vp);

	// プロジェクションマトリクス設定
	DirectX::XMMATRIX projMatrix = DirectX::XMMatrixPerspectiveFovLH(
		DirectX::XMConvertToRadians(mWorld.fov),
		(float)vp.Width / (float)vp.Height,
		mWorld.nearZ,
		mWorld.farZ
	);

	Direct3D11::getInst()->setUpConstantBuffer(viewMatrix, projMatrix);
}

//-------------------------------------------------------------------------------------------------
void Camera::draw()
{
}

} // namespace
// EOF
