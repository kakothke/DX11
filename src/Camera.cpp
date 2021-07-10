#include "Camera.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto D3D11 = Direct3D11::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Camera::Camera()
	: mFov(60.0f)
	, mNearZ(0.3f)
	, mFarZ(1000.0f)
{
	mTransform.pos = Vector3(0.0f, 1.0f, -10.0f);
	setTag(GameObjectTag::Camera);
}

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
/// @param aTransform �g�����X�t�H�[��
Camera::Camera(Transform aTransform)
	: mFov(60.0f)
	, mNearZ(0.3f)
	, mFarZ(1000.0f)
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
	mTransform.pos = Vector3(0.0f, 1.0f, -10.0f);
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
/// �f�X�g���N�^
Camera::~Camera()
{
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void Camera::update()
{
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
	D3D11->getConstantBuffer()->setMatrixV(mTransform);
	D3D11->getConstantBuffer()->setMatrixP(mFov, mNearZ, mFarZ);
	D3D11->getConstantBuffer()->updateCamera(mTransform.pos);
}

} // namespace
// EOF
