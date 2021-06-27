#include "Camera.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �萔
const static float DEFINE_FOV = 60.0f;
const static float DEFINE_NEAR = 0.3f;
const static float DEFINE_FAR = 1000.0f;
const static Vector3 DEFINE_POS = Vector3(0.0f, 1.0f, -10.0f);

//-------------------------------------------------------------------------------------------------
/// �V���O���g���N���X
const static auto D3D11 = Direct3D11::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Camera::Camera()
	: mFov(DEFINE_FOV)
	, mNearZ(DEFINE_NEAR)
	, mFarZ(DEFINE_FAR)
{
	mTransform.pos = DEFINE_POS;
	setTag(GameObjectTag::Camera);
}

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
/// @param aTransform �g�����X�t�H�[��
Camera::Camera(Transform aTransform)
	: mFov(DEFINE_FOV)
	, mNearZ(DEFINE_NEAR)
	, mFarZ(DEFINE_FAR)
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
	mTransform.pos = DEFINE_POS;
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
	D3D11->getConstantBuffer()->setMatrixV(mTransform);
	D3D11->getConstantBuffer()->setMatrixP(mFov, mNearZ, mFarZ);
	D3D11->getConstantBuffer()->updateCamera(mTransform.pos);
}

} // namespace
// EOF
