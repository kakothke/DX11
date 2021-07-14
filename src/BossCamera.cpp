#include "BossCamera.h"

//-------------------------------------------------------------------------------------------------
#include "TestPlayer.h"
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
BossCamera::BossCamera()
	: mPlayer(nullptr)
	, mDistanceFromPlayer(20.0f)
{
}

//-------------------------------------------------------------------------------------------------
/// ������
void BossCamera::initialize()
{
	mPlayer = (TestPlayer*)mGameObjectList->findWorldGameObject(GameObjectTag::Player);
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void BossCamera::update()
{
	// �v���C���[��e�I�u�W�F�N�g�Ƃ��ĘA��������
	mTransform = mPlayer->transform();
	mTransform.localPos = -mPlayer->moveVelocity();
	mTransform.localPos.z = -mDistanceFromPlayer;
}

//-------------------------------------------------------------------------------------------------
/// �`��
void BossCamera::draw()
{
}

} // namespace
// EOF
