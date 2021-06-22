#include "GameCamera.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
GameCamera::GameCamera()
{
}

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
/// @param aTransform �g�����X�t�H�[��
GameCamera::GameCamera(Transform aTransform) : Camera(aTransform)
{
}

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
/// @param aCameraParam �J�����p�����[�^ x(Fov) / y(Near) / z(Far)
GameCamera::GameCamera(Vector3 aCameraParam) : Camera(aCameraParam)
{
}

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
/// @param aTransform �g�����X�t�H�[��
/// @param aCameraParam �J�����p�����[�^ x(Fov) / y(Near) / z(Far)
GameCamera::GameCamera(Transform aTransform, Vector3 aCameraParam) : Camera(aTransform, aCameraParam)
{
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void GameCamera::update()
{
	updateConstantBuffer();
}

//-------------------------------------------------------------------------------------------------
/// �`��
void GameCamera::draw()
{
}

} // namespace
// EOF
