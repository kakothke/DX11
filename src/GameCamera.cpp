#include "GameCamera.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
GameCamera::GameCamera()
	: mLocalTransform()
	, mPlayerTransform()
	, mDirectionFromPlayer(30.0f)
{
	mTransform.pos.z = 50;
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void GameCamera::update()
{
	// ���[�J���ʒu��ݒ�
	mLocalTransform.pos.z = -mDirectionFromPlayer;

	// �v���C���[��e�I�u�W�F�N�g�Ƃ��ĘA��������
	DirectX::XMMATRIX transform = mLocalTransform.worldMatrix() * mPlayerTransform.worldMatrix();
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
/// �v���C���[�̃g�����X�t�H�[�����擾����
/// @param aTransform �g�����X�t�H�[��
void GameCamera::setPlayerTransform(const Transform& aTransform)
{
	mPlayerTransform = aTransform;
}

} // namespace
// EOF
