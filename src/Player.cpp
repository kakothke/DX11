#include "Player.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "InputManager.h"
#include "Sound.h"
#include "Math.h"
#include "BoosterEffect.h"
#include "ExplosionEffect.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto INPUT_MANAGER = InputManager::getInst();
const static auto FPS = Fps::getInst();
const static auto SOUND = Sound::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Player::Player()
	: mMoveSpeed(20.0f)
	, mInstanceBoosterTimer(0.0f)
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
	instanceEffect();
}

//-------------------------------------------------------------------------------------------------
/// �`��
void Player::draw()
{
	mRenderer.render(mTransform);
}

//-------------------------------------------------------------------------------------------------
void Player::missEvent()
{
	SOUND->playOneShot((int)SoundList::SE_Miss);
	mGameObjectList->instanceToWorldAlpha(new ExplosionEffect(mTransform.pos), 1);
	setActive(false);
}

//-------------------------------------------------------------------------------------------------
/// �ړ�
void Player::move()
{
	// �萔
	const static float NORMAL_SPEED_LEVEL = 20.0f;
	const static float HIGH_SPEED_LEVEL = NORMAL_SPEED_LEVEL * 2.0f;
	const static float LOW_SPEED_LEVEL = NORMAL_SPEED_LEVEL / 2.0f;

	float speed = 10.0f * FPS->deltaTime();
	float axisY = INPUT_MANAGER->axesRaw().y;
	if (axisY == 1) {
		// �����ړ�
		if (mMoveSpeed != HIGH_SPEED_LEVEL) {
			mMoveSpeed = Math::Lerp(mMoveSpeed, HIGH_SPEED_LEVEL, speed);
		}
	} else if (axisY == -1) {
		// �����ړ�
		if (mMoveSpeed != LOW_SPEED_LEVEL) {
			mMoveSpeed = Math::Lerp(mMoveSpeed, LOW_SPEED_LEVEL, speed);
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

	// �ړ��ł���[�𐧌�
	mTransform.pos.x = Math::Clamp(mTransform.pos.x, -50.0f, 50.0f);
}

//-------------------------------------------------------------------------------------------------
/// �V���b�g
void Player::shot()
{
}

//-------------------------------------------------------------------------------------------------
/// �G�t�F�N�g����
void Player::instanceEffect()
{
	const static float INSTANCE_BOOSTER_TIME = 0.05f;
	const static float SCALE_RANGE = 0.25f;

	if (mInstanceBoosterTimer > INSTANCE_BOOSTER_TIME) {
		mInstanceBoosterTimer = 0.0f;
		Transform transform = mTransform;
		float axisY = INPUT_MANAGER->axesRaw().y;
		if (axisY == 1) {
			transform.scale += SCALE_RANGE;
			SOUND->playOneShot((int)SoundList::SE_Booster_High);
		} else if (axisY == -1) {
			transform.scale -= SCALE_RANGE;
			SOUND->playOneShot((int)SoundList::SE_Booster_Low);
		} else {
			SOUND->playOneShot((int)SoundList::SE_Booster_Normal);
		}
		mGameObjectList->instanceToWorldAlpha(new BoosterEffect(transform), 1);
	} else {
		mInstanceBoosterTimer += FPS->deltaTime();
	}
}

} // namespace
// EOF
