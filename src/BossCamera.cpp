#include "BossCamera.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �萔
const static float DEFINE_DISTANCE = 20.0f;

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
BossCamera::BossCamera()
	: mLocalTransform()
	, mPlayerTransform()
	, mPlayerVelocity()
	, mDistanceFromPlayer(DEFINE_DISTANCE)
{
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void BossCamera::update()
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
void BossCamera::draw()
{
}

//-------------------------------------------------------------------------------------------------
/// �v���C���[�̃g�����X�t�H�[����ݒ肷��
/// @param aTransform �g�����X�t�H�[��
void BossCamera::setPlayerTransform(const Transform& aTransform)
{
	mPlayerTransform = aTransform;
}

//-------------------------------------------------------------------------------------------------
/// �v���C���[�̈ړ����x��ݒ肷��
/// @param aVelocity 
void BossCamera::setPlayerVelocity(const Vector2& aVelocity)
{
	mPlayerVelocity = aVelocity;
}

} // namespace
// EOF
