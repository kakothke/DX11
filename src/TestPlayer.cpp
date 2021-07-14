#include "TestPlayer.h"

//-------------------------------------------------------------------------------------------------
#include "MyOutputDebugString.h" 
#include "ResourceFileName.h"
#include "InputManager.h"
#include "Math.h"
#include "Sound.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto INPUT_MANAGER = InputManager::getInst();
const static auto FPS = Fps::getInst();
const static auto SOUND = Sound::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
TestPlayer::TestPlayer()
	: mRenderer()
	, mTargetDistance(100.0f)
	, mMoveVelocity(0)
{
	// �^�O
	setTag(GameObjectTag::Player);

	// �`��ݒ�
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::Player));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
TestPlayer::~TestPlayer()
{
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void TestPlayer::update()
{
	// �^�[�Q�b�g�ʒu�X�V
	const static auto BOSS_OBJ = mGameObjectList->findGameObject(GameObjectTag::Boss);
	mTargetPos = BOSS_OBJ->transform().pos;

	// �ړ�
	move();
	// �V���b�g
	shot();
}

//-------------------------------------------------------------------------------------------------
/// �`��
void TestPlayer::draw()
{
	mRenderer.render(mTransform);
}

//-------------------------------------------------------------------------------------------------
/// �ړ����x���擾����
/// @return �ړ����x
const Vector2& TestPlayer::moveVelocity()
{
	return mMoveVelocity;
}

//-------------------------------------------------------------------------------------------------
/// �ړ�
void TestPlayer::move()
{
	const static float MOVE_SPEED = 50.0f;

	// �ړ�
	mMoveVelocity = INPUT_MANAGER->axes();
	if (mMoveVelocity.Magnitude() > 1.0f) {
		mMoveVelocity = mMoveVelocity.Normalized();
	}

	// �g�����X�t�H�[���X�V
	Vector2 angle = mMoveVelocity * FPS->deltaTime() * MOVE_SPEED;
	mTransform.rot *= Quaternion::AxisAngle(-mTransform.Up(), angle.x);
	mTransform.rot *= Quaternion::AxisAngle(mTransform.Right(), angle.y);
	mTransform.pos = mTargetPos + mTransform.rot * Vector3::back * mTargetDistance;
}

//-------------------------------------------------------------------------------------------------
/// �V���b�g
void TestPlayer::shot()
{
	const static float RAPID_SHOT_TIME = 0.05f;
	const static float RESET_SCALE_TIME = 10.0f;
	const static Vector2 SHOT_SCALE = Vector2(1.5f, 0.5f);

	if (INPUT_MANAGER->getButton(InputCode::OK)) {
		// �V���b�g
		if (mRapidShotTimer == 0.0f) {
			// SE�Đ�
			SOUND->playOneShot((int)SoundList::SE_Shot);
			// �̂��k�܂���
			mTransform.scale = SHOT_SCALE;
			// �e����
			Transform bulletTransform;
			bulletTransform = mTransform;
			mGameObjectList->instanceToWorldAlpha(new PlayerBullet(bulletTransform, mTargetPos));
		}
		// �^�C�}�[�X�V
		if (mRapidShotTimer < RAPID_SHOT_TIME) {
			mRapidShotTimer += FPS->deltaTime();
		} else {
			mRapidShotTimer = 0.0f;
		}
	} else {
		mRapidShotTimer = 0.0f;
	}
	// �V���b�g�������đ̂��k��ł�����߂�
	if (mTransform.scale != Vector3(0.0f)) {
		mTransform.scale.x -= RESET_SCALE_TIME * FPS->deltaTime();
		mTransform.scale.y += RESET_SCALE_TIME * FPS->deltaTime();
		mTransform.scale.x = Math::Clamp(mTransform.scale.x, 1.0f, SHOT_SCALE.x);
		mTransform.scale.y = Math::Clamp(mTransform.scale.y, SHOT_SCALE.y, 1.0f);
	}
}

} // namespace
// EOF
