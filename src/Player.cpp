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

	for (auto itr = mPlayerBullet.begin(); itr != mPlayerBullet.end();) {
		if ((*itr)->activeSelf()) {
			(*itr)->update();
			itr++;
		} else {
			itr = mPlayerBullet.erase(itr);
		}
	}
}

//-------------------------------------------------------------------------------------------------
/// �`��
void Player::draw()
{
	mRenderer.render(mTransform);

	for (const auto bullet : mPlayerBullet) {
		bullet->draw();
	}
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
	// �ړ�
	mMoveVelocity = INPUT_MANAGER->axes();
	if (mMoveVelocity.Magnitude() > 1.0f) {
		mMoveVelocity = mMoveVelocity.Normalized();
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
	if (INPUT_MANAGER->getButton(InputCode::OK)) {
		// �V���b�g
		if (timer == 0) {
			// SE�Đ�
			SOUND->playOneShot((int)SoundList::SE_Shot);
			// �̂��k�܂���
			mTransform.scale.x = DEFINE_SHOT_SIZE.x;
			mTransform.scale.y = DEFINE_SHOT_SIZE.y;
			// �e����
			Transform bulletTransform;
			bulletTransform = mTransform;
			float offset = 2.0f;
			bulletTransform.pos += bulletTransform.Right() * offset;
			mPlayerBullet.emplace_back(std::make_shared<PlayerBullet>(bulletTransform, mTargetPos));
			bulletTransform = mTransform;
			bulletTransform.pos += -bulletTransform.Right() * offset;
			mPlayerBullet.emplace_back(std::make_shared<PlayerBullet>(bulletTransform, mTargetPos));
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
