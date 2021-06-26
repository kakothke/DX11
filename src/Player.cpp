#include "Player.h"

//-------------------------------------------------------------------------------------------------
#include "MyOutputDebugString.h" 
#include "ResourceFileName.h"
#include "InputManager.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
static const float MOVE_SPEED = 0.05f;

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Player::Player()
{
	initialize();
}

//-------------------------------------------------------------------------------------------------
/// ����������
void Player::initialize()
{
	// �`��ݒ�
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::Player));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));

	// �����ݒ�
	mDistanceFromBoss = 100;
	mPoseMat = DirectX::XMMatrixIdentity();
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void Player::update()
{
	move();
	shot();
}

//-------------------------------------------------------------------------------------------------
/// �`��
void Player::draw()
{
	mRenderer.render(mTransform);
}

//-------------------------------------------------------------------------------------------------
/// �{�X�̈ʒu��ݒ肷��
/// @param aPos 
void Player::setBossPos(const Vector3& aPos)
{
	mBossPos = aPos;
}

//-------------------------------------------------------------------------------------------------
/// �ړ�
void Player::move()
{
	static auto input = InputManager::getInst();
	Vector3 axis;
	axis.x = input->getAxes().y;
	axis.y = -input->getAxes().x;
	Quaternion rotQ = Quaternion::AxisAngle(axis, 0.01f);
	mTransform.pos -= mBossPos;
	mTransform.pos *= rotQ;
	mTransform.rot *= rotQ;
	mTransform.pos += mBossPos;
}

//-------------------------------------------------------------------------------------------------
/// �V���b�g
void Player::shot()
{

}

} // namespace
// EOF
