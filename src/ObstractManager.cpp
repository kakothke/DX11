#include "ObstractManager.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �萔
const static float DEFINE_INSTANCE_TIME = 0.2f;
const static float DEFINE_LEVEL_UP_TIME = 5.0f;
const static float DEFINE_MOVE_SPEED = 100.0f;
const static float DEFINE_MOVE_UP = 5.0f;

//-------------------------------------------------------------------------------------------------
/// �V���O���g��
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
ObstractManager::ObstractManager()
	: mSpeed(DEFINE_MOVE_SPEED)
	, mLevel(1)
{
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
ObstractManager::~ObstractManager()
{
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void ObstractManager::update()
{
	// ���x���A�b�v
	static float time = 0.0f;
	if (time > DEFINE_LEVEL_UP_TIME * mLevel) {
		time = 0.0f;
		mLevel++;
		mSpeed += DEFINE_MOVE_UP;
	} else {
		time += FPS->deltaTime();
	}

	// ����
	instanceObj();

	// �n�`�X�V
	for (auto itr = mGround.begin(); itr != mGround.end();) {
		if ((*itr)->activeSelf()) {
			// �X�V
			(*itr)->update();
			itr++;
		} else {
			// ����
			itr = mGround.erase(itr);
		}
	}
	// ��Q���X�V
	for (auto itr = mObstract.begin(); itr != mObstract.end();) {
		if ((*itr)->activeSelf()) {
			// �X�V
			(*itr)->update();
			itr++;
		} else {
			// ����
			itr = mObstract.erase(itr);
		}
	}
}

//-------------------------------------------------------------------------------------------------
/// �`��
void ObstractManager::draw()
{
	for (const auto ground : mGround) {
		ground->draw();
	}
	for (const auto obstract : mObstract) {
		obstract->draw();
	}
}

//-------------------------------------------------------------------------------------------------
/// �����蔻��
bool ObstractManager::collisionPlayer(const Vector3& aPos)
{
	const static float playerSize = 0.5f;
	for (const auto obstract : mObstract) {
		const auto obs = obstract->getCollision();
		if (obs.pos.x - obs.scale.x / 2.0f < aPos.x + playerSize &&
			obs.pos.x + obs.scale.x / 2.0f > aPos.x - playerSize &&
			obs.pos.y - obs.scale.y / 2.0f < aPos.y + playerSize &&
			obs.pos.y + obs.scale.y / 2.0f > aPos.y - playerSize &&
			obs.pos.z - obs.scale.z / 2.0f < aPos.z + playerSize &&
			obs.pos.z + obs.scale.z / 2.0f > aPos.z - playerSize) {
			return true;
		}
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
/// �I�u�W�F�N�g�𐶐�����
void ObstractManager::instanceObj()
{
	static float groundTimer = 0.0f;
	static float obstractTimer = 0.0f;
	// �n�㐶��
	if (groundTimer > DEFINE_INSTANCE_TIME / 2.0f) {
		groundTimer = 0.0f;
		instanceGround();
	} else {
		groundTimer += FPS->deltaTime();
	}
	// ��Q������
	if (obstractTimer > DEFINE_INSTANCE_TIME) {
		obstractTimer = 0.0f;
		instanceObstract();
	} else {
		obstractTimer += FPS->deltaTime();
	}
}

//-------------------------------------------------------------------------------------------------
/// �n��𐶐�����
void ObstractManager::instanceGround()
{
	static Transform transform = Transform(
		Vector3(0.0f, 0.0f, 300.0f),
		Vector3(0.0f),
		Vector3(16.0f, 5.0f, 16.0f)
	);
	for (int i = 0; i < 2; i++) {
		static int randPosX = 100;
		static int randPosY = 3;
		static float instPosY = 8.0f;
		transform.pos.x = (rand() % randPosX) - (randPosX / 2.0f);
		transform.pos.y = (rand() % randPosY) - instPosY;
		mGround.emplace_back(std::make_shared<Ground>(transform, mSpeed));
	}
}

//-------------------------------------------------------------------------------------------------
/// ��Q���𐶐�����
void ObstractManager::instanceObstract()
{
	static Transform transform = Transform(
		Vector3(0.0f, -3.0f, 300.0f),
		Vector3(0.0f),
		Vector3(1.0f, 2.5f, 1.0f)
	);
	for (int i = 0; i < mLevel; i++) {
		static int randPosX = 1000;
		static int randScale = 3;
		transform.pos.x = ((rand() % randPosX) * 0.1f) - ((randPosX * 0.1f) / 2.0f);
		transform.scale.x = (rand() % randScale + 1.0f);
		mObstract.emplace_back(std::make_shared<Obstract>(transform, mSpeed));
	}
}

//-------------------------------------------------------------------------------------------------
/// �X�s�[�h�ύX
void ObstractManager::changeSpeed()
{
	for (const auto ground : mGround) {
		ground->setMoveSpeed(mSpeed);
	}
	for (const auto obstract : mObstract) {
		obstract->setMoveSpeed(mSpeed);
	}
}

} // namespace
// EOF