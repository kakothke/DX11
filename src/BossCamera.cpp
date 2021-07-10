#include "BossCamera.h"

//-------------------------------------------------------------------------------------------------
#include "TestPlayer.h"
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
BossCamera::BossCamera()
	: mDistanceFromPlayer(20.0f)
{
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void BossCamera::update()
{
	const static auto PLAYER_OBJ = (TestPlayer*)mGameObjectList->findGameObject(GameObjectTag::Player);

	// �v���C���[��e�I�u�W�F�N�g�Ƃ��ĘA��������
	mTransform = PLAYER_OBJ->transform();
	mTransform.localPos = -PLAYER_OBJ->moveVelocity();
	mTransform.localPos.z = -mDistanceFromPlayer;
}

//-------------------------------------------------------------------------------------------------
/// �`��
void BossCamera::draw()
{
}

} // namespace
// EOF
