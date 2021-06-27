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
	// ���[�J���ʒu��ݒ�
	mLocalTransform.pos = -mPlayerVelocity;
	mLocalTransform.pos.z = -mDistanceFromPlayer;

	// �v���C���[��e�I�u�W�F�N�g�Ƃ��ĘA��������
	DirectX::XMMATRIX transform = mLocalTransform.WorldMatrix() * mPlayerTransform.WorldMatrix();
	mTransform.pos.x = transform.r[3].m128_f32[0];
	mTransform.pos.y = transform.r[3].m128_f32[1];
	mTransform.pos.z = transform.r[3].m128_f32[2];
	mTransform.rot = -mPlayerTransform.rot;

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
