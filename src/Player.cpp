#include "Player.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "InputManager.h"
#include "Math.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto INPUT_MANAGER = InputManager::getInst();
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Player::Player()
	: mMoveSpeed(20.0f)
{
	// �^�O�ݒ�
	setTag(GameObjectTag::Player);

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
	// �萔
	const static float NORMAL_SPEED_LEVEL = 20.0f;
	const static float UP_SPEED_LEVEL = NORMAL_SPEED_LEVEL * 2.0f;
	const static float DOWN_SPEED_LEVEL = NORMAL_SPEED_LEVEL / 2.0f;

	float speed = 10.0f * FPS->deltaTime();
	if (INPUT_MANAGER->axesRaw().y == 1) {
		// �����ړ�
		if (mMoveSpeed != UP_SPEED_LEVEL) {
			mMoveSpeed = Math::Lerp(mMoveSpeed, UP_SPEED_LEVEL, speed);
		}
	} else if (INPUT_MANAGER->axesRaw().y == -1) {
		// �����ړ�
		if (mMoveSpeed != DOWN_SPEED_LEVEL) {
			mMoveSpeed = Math::Lerp(mMoveSpeed, DOWN_SPEED_LEVEL, speed);
		}
	} else {
		// �ʏ�ړ�
		if (mMoveSpeed != NORMAL_SPEED_LEVEL) {
			mMoveSpeed = Math::Lerp(mMoveSpeed, NORMAL_SPEED_LEVEL, speed);
		}
	}

	// �ړ�
	float move = INPUT_MANAGER->axesRaw().x * mMoveSpeed;
	float rot = INPUT_MANAGER->axes().x * -mMoveSpeed * 2.0f;
	mTransform.pos.x += move * FPS->deltaTime();
	mTransform.rot = Quaternion::Euler(Vector3(0.0f, 0.0f, rot));
}

//-------------------------------------------------------------------------------------------------
/// �V���b�g
void Player::shot()
{
}

} // namespace
// EOF
