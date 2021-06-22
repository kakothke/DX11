#include "Camera.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Camera::Camera()
	: mFov(60)
	, mNearZ(0.3f)
	, mFarZ(1000)
{
	mTransform.pos = Vector3(0, 1, -10);
	setTag(GameObjectTag::Camera);
}

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
/// @param aTransform �g�����X�t�H�[��
Camera::Camera(Transform aTransform)
	: mFov(60)
	, mNearZ(0.3f)
	, mFarZ(1000)
{
	mTransform = aTransform;
	setTag(GameObjectTag::Camera);
}

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
/// @param aCameraParam �J�����p�����[�^ x(Fov) / y(Near) / z(Far)
Camera::Camera(Vector3 aCameraParam)
	: mFov(aCameraParam.x)
	, mNearZ(aCameraParam.y)
	, mFarZ(aCameraParam.z)
{
	mTransform.pos = Vector3(0, 1, -10);
	setTag(GameObjectTag::Camera);
}

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
/// @param aTransform �g�����X�t�H�[��
/// @param aCameraParam �J�����p�����[�^ x(Fov) / y(Near) / z(Far)
Camera::Camera(Transform aTransform, Vector3 aCameraParam)
	: mFov(aCameraParam.x)
	, mNearZ(aCameraParam.y)
	, mFarZ(aCameraParam.z)
{
	mTransform = aTransform;
	setTag(GameObjectTag::Camera);
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void Camera::update()
{
	updateConstantBuffer();
}

//-------------------------------------------------------------------------------------------------
/// �`��
void Camera::draw()
{
}

//-------------------------------------------------------------------------------------------------
/// �R���X�^���g�o�b�t�@���X�V����
void Camera::updateConstantBuffer()
{
	DirectX::XMFLOAT3 camera(mFov, mNearZ, mFarZ);
	const static auto cBuf = Direct3D11::getInst()->getConstantBuffer();
	cBuf->setMatrixVP(mTransform.XMFLOAT3X3(), camera);
	cBuf->updateCamera(mTransform.pos.XMVECTOR(), mTransform.rot.XMVECTOR());
}

} // namespace
// EOF
