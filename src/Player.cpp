#include "Player.h"

//-------------------------------------------------------------------------------------------------
#include "MyOutputDebugString.h" 
#include "ResourceFileName.h"
#include "InputManager.h"
#include "Math.h"
#include "Sound.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �萔
/// �^�[�Q�b�g����̃f�t�H���g����
const static float DEFINE_TARGET_DISTANCE = 100.0f;
/// �ő�ړ����x
const static float DEFINE_MAX_VELOCITY = 1.0f;
/// �����x
const static float DEFINE_MOVE_SPEED = 10.0f;
/// �A���ŃV���b�g�����Ă鎞��
const static float DEFINE_SHOT_TIME = 0.05f;
/// �V���b�g���̃A�j���[�V�����p
const static Vector2 DEFINE_SHOT_SIZE = Vector2(1.5f, 0.5f);

//-------------------------------------------------------------------------------------------------
/// �V���O���g���N���X
const static auto INPUT_MANAGER = InputManager::getInst();
const static auto FPS = Fps::getInst();
const static auto SOUND = Sound::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Player::Player()
	: mRenderer()
	, mTargetPos()
	, mTargetDistance(DEFINE_TARGET_DISTANCE)
	, mMoveVelocity(0)
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
/// �ړ����x���擾����
/// @return �ړ����x
const Vector2& Player::moveVelocity()
{
	return mMoveVelocity;
}

//-------------------------------------------------------------------------------------------------
/// �^�[�Q�b�g�̈ʒu��ݒ肷��
/// @param aPos �^�[�Q�b�g�̈ʒu
void Player::setTargetPos(const Vector3& aPos)
{
	mTargetPos = aPos;
}

//-------------------------------------------------------------------------------------------------
/// �ړ�
void Player::move()
{
	// ����
	Vector2 inputAxis = INPUT_MANAGER->getAxes();

	// �΂ߓ���
	float maxVelocity = DEFINE_MAX_VELOCITY;
	if (inputAxis.SqrMagnitude() == 2) {
		maxVelocity /= sqrtf(2);
	}

	// �ړ�
	if (inputAxis.x > 0) {
		mMoveVelocity.x = Math::Lerp(mMoveVelocity.x, maxVelocity, FPS->deltaTime() * DEFINE_MOVE_SPEED);
	}
	if (inputAxis.x < 0) {
		mMoveVelocity.x = Math::Lerp(mMoveVelocity.x, -maxVelocity, FPS->deltaTime() * DEFINE_MOVE_SPEED);
	}
	if (inputAxis.y > 0) {
		mMoveVelocity.y = Math::Lerp(mMoveVelocity.y, maxVelocity, FPS->deltaTime() * DEFINE_MOVE_SPEED);
	}
	if (inputAxis.y < 0) {
		mMoveVelocity.y = Math::Lerp(mMoveVelocity.y, -maxVelocity, FPS->deltaTime() * DEFINE_MOVE_SPEED);
	}
	// �Î~
	if (inputAxis.x == 0) {
		mMoveVelocity.x = Math::Lerp(mMoveVelocity.x, 0, FPS->deltaTime() * DEFINE_MOVE_SPEED);
	}
	if (inputAxis.y == 0) {
		mMoveVelocity.y = Math::Lerp(mMoveVelocity.y, 0, FPS->deltaTime() * DEFINE_MOVE_SPEED);
	}

	// �g�����X�t�H�[���X�V
	Vector2 angle = mMoveVelocity * FPS->deltaTime();
	mTransform.rot *= Quaternion::AxisAngle(mTransform.Up(), -angle.x);
	mTransform.rot *= Quaternion::AxisAngle(mTransform.Right(), angle.y);
	mTransform.pos = mTargetPos + mTransform.rot * Vector3::back * mTargetDistance;
}

//-------------------------------------------------------------------------------------------------
/// �V���b�g
void Player::shot()
{
	static float timer = 0;
	if (INPUT_MANAGER->getInput(InputCode::OK)) {
		// �V���b�g
		if (timer == 0) {
			// SE�Đ�
			SOUND->playOneShot((int)SoundList::SE_Shot);
			// �̂��k�܂���
			mTransform.scale.x = DEFINE_SHOT_SIZE.x;
			mTransform.scale.y = DEFINE_SHOT_SIZE.y;
		}
		// �^�C�}�[�X�V
		if (timer < DEFINE_SHOT_TIME) {
			timer += FPS->deltaTime();
		} else {
			timer = 0;
		}
	} else if (timer > 0) {
		// �V���b�g�{�^���𗣂�����^�C�}�[���Z�b�g
		timer = 0;
	}
	// �V���b�g�������đ̂��k��ł�����߂�
	if (mTransform.scale != Vector3(0)) {
		mTransform.scale.x -= 10.0f * FPS->deltaTime();
		mTransform.scale.y += 10.0f * FPS->deltaTime();
		mTransform.scale.x = Math::Clamp(mTransform.scale.x, 1.0f, DEFINE_SHOT_SIZE.x);
		mTransform.scale.y = Math::Clamp(mTransform.scale.y, DEFINE_SHOT_SIZE.y, 1.0f);
	}
}

} // namespace
// EOF
