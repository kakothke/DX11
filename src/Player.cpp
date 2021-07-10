#include "Player.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "InputManager.h"
#include "Math.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static float DEFINE_MOVE_SPEED = 20.0f;
const static float DEFINE_MOVE_ROT = 45.0f;
const static float DEFINE_SPEED_DOWN = 2.0f;
const static float DEFINE_SPEED_DOWN_SPEED = 10.0f;
const static Vector3 DEFINE_POS = Vector3(0.0f, 0.0f, 10.0f);

//-------------------------------------------------------------------------------------------------
const static auto INPUT_MANAGER = InputManager::getInst();
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Player::Player()
	: mMoveSpeed(DEFINE_MOVE_SPEED)
	, mMoveRot(DEFINE_MOVE_ROT)
{
	// �g�����X�t�H�[���ݒ�
	mTransform.pos = DEFINE_POS;

	// �`��ݒ�
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::Player));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
Player::~Player()
{
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
/// �ړ�
void Player::move()
{
	// �����ړ�
	float speed = DEFINE_SPEED_DOWN_SPEED * FPS->deltaTime();
	if (INPUT_MANAGER->axesRaw().y == -1) {
		if (mMoveSpeed != DEFINE_MOVE_SPEED / DEFINE_SPEED_DOWN) {
			mMoveSpeed = Math::Lerp(mMoveSpeed, DEFINE_MOVE_SPEED / DEFINE_SPEED_DOWN, speed);
		}
		if (mMoveRot != DEFINE_MOVE_ROT / (DEFINE_SPEED_DOWN * 2.0f)) {
			mMoveRot = Math::Lerp(mMoveRot, DEFINE_MOVE_ROT / (DEFINE_SPEED_DOWN * 2.0f), speed);
		}
	} else {
		if (mMoveSpeed < DEFINE_MOVE_SPEED) {
			mMoveSpeed = Math::Lerp(mMoveSpeed, DEFINE_MOVE_SPEED, speed);
		}
		if (mMoveSpeed < DEFINE_MOVE_ROT) {
			mMoveRot = Math::Lerp(mMoveRot, DEFINE_MOVE_ROT, speed);
		}
	}
	
	// �ړ�
	float move = INPUT_MANAGER->axesRaw().x * mMoveSpeed;
	float rot = INPUT_MANAGER->axes().x * mMoveRot;
	mTransform.rot = Quaternion::Euler(Vector3(0.0f, 0.0f, -rot));
	mTransform.pos.x += move * FPS->deltaTime();
}

//-------------------------------------------------------------------------------------------------
/// �V���b�g
void Player::shot()
{
}

} // namespace
// EOF
