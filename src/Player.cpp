#include "Player.h"

//-------------------------------------------------------------------------------------------------
#include "MyOutputDebugString.h" 
#include "ResourceFileName.h"
#include "InputManager.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �萔
const static float DEFINE_TARGET_DISTANCE = 100.0f;
const static float DEFINE_MOVE_VELOCITY = 0.05f;

//-------------------------------------------------------------------------------------------------
/// �V���O���g���N���X
const static auto INPUT_MANAGER = InputManager::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Player::Player()
	: mRenderer()
	, mTargetPos()
	, mTargetDistance(DEFINE_TARGET_DISTANCE)
	, mMoveVelocity(DEFINE_MOVE_VELOCITY)
{
	// �`��ݒ�
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::Player));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));
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
	mTargetPos = aPos;
}

//-------------------------------------------------------------------------------------------------
/// �ړ�
void Player::move()
{
	// ����
	Vector2 axis = INPUT_MANAGER->getAxes();
	// �ړ�
	mTransform.rot *= Quaternion::AxisAngle(mTransform.Up() * -axis.x, mMoveVelocity);
	mTransform.rot *= Quaternion::AxisAngle(mTransform.Right() * axis.y, mMoveVelocity);
	mTransform.pos = mTargetPos + mTransform.rot * Vector3::back * mTargetDistance;
}

//-------------------------------------------------------------------------------------------------
/// �V���b�g
void Player::shot()
{

}

} // namespace
// EOF
