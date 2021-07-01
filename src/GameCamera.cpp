#include "GameCamera.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �萔
const static float DEFINE_DISTANCE = 20.0f;

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
GameCamera::GameCamera()
	: mLocalTransform()
	, mPlayerTransform()
	, mPlayerVelocity()
	, mDistanceFromPlayer(DEFINE_DISTANCE)
{
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void GameCamera::update()
{
	// �v���C���[��e�I�u�W�F�N�g�Ƃ��ĘA��������
	mTransform = mPlayerTransform;
	mTransform.localPos = -mPlayerVelocity;
	mTransform.localPos.z = -mDistanceFromPlayer;

	// �R���X�^���g�o�b�t�@�X�V
	updateConstantBuffer();
}

//-------------------------------------------------------------------------------------------------
/// �`��
void GameCamera::draw()
{
}

//-------------------------------------------------------------------------------------------------
/// �v���C���[�̃g�����X�t�H�[����ݒ肷��
/// @param aTransform �g�����X�t�H�[��
void GameCamera::setPlayerTransform(const Transform& aTransform)
{
	mPlayerTransform = aTransform;
}

//-------------------------------------------------------------------------------------------------
/// �v���C���[�̈ړ����x��ݒ肷��
/// @param aVelocity 
void GameCamera::setPlayerVelocity(const Vector2& aVelocity)
{
	mPlayerVelocity = aVelocity;
}

} // namespace
// EOF
