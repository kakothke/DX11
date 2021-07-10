#include "ObstractManager.h"

//-------------------------------------------------------------------------------------------------
#include "Ground.h"
#include "Obstract.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
ObstractManager::ObstractManager()
	: mLevelUpTimer(0.0f)
	, mInstanceObstractTimer(0.0f)
	, mInstanceGroundTimer(0.0f)
	, mMoveSpeed(100.0f)
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
	updateLevel();
	instanceObj();
}

//-------------------------------------------------------------------------------------------------
/// �`��
void ObstractManager::draw()
{
}

//-------------------------------------------------------------------------------------------------
/// �����蔻��
bool ObstractManager::collisionPlayer(const Vector3& aPos)
{
	/*const static float playerSize = 0.5f;
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
	}*/
	return false;
}

//-------------------------------------------------------------------------------------------------
/// ���x���X�V
void ObstractManager::updateLevel()
{
	// �萔
	const static float LEVEL_UP_TIME = 5.0f;
	const static float SPEED_UP = 5.0f;

	// ���x���A�b�v
	if (mLevelUpTimer > LEVEL_UP_TIME * mLevel) {
		mLevelUpTimer = 0.0f;
		mLevel++;
		mMoveSpeed += SPEED_UP;
		changeSpeed();
	} else {
		mLevelUpTimer += FPS->deltaTime();
	}
}

//-------------------------------------------------------------------------------------------------
/// �I�u�W�F�N�g�𐶐�����
void ObstractManager::instanceObj()
{
	const static float INSTANCE_OBSTRACT_TIME = 0.2f;
	const static float INSTANCE_GROUND_TIME = 0.1f;

	// ��Q������
	if (mInstanceObstractTimer > INSTANCE_OBSTRACT_TIME) {
		mInstanceObstractTimer = 0.0f;
		instanceObstract();
	} else {
		mInstanceObstractTimer += FPS->deltaTime();
	}

	// �n�㐶��
	if (mInstanceGroundTimer > INSTANCE_GROUND_TIME) {
		mInstanceGroundTimer = 0.0f;
		instanceGround();
	} else {
		mInstanceGroundTimer += FPS->deltaTime();
	}
}

//-------------------------------------------------------------------------------------------------
/// �n��𐶐�����
void ObstractManager::instanceGround()
{
	Transform transform = Transform(
		Vector3(0.0f, -8.0f, 300.0f),
		Vector3(0.0f),
		Vector3(16.0f, 5.0f, 16.0f)
	);

	for (int i = 0; i < 2; i++) {
		const static int RANDOM_POS_X = 100;
		const static int RANDOM_POS_Y = 3;
		transform.pos.x = (rand() % RANDOM_POS_X) - (RANDOM_POS_X / 2.0f);
		transform.pos.y += rand() % RANDOM_POS_Y;
		mGameObjectList->setGameObjectListToWorld(new Ground(transform, mMoveSpeed));
	}
}

//-------------------------------------------------------------------------------------------------
/// ��Q���𐶐�����
void ObstractManager::instanceObstract()
{
	Transform transform = Transform(
		Vector3(0.0f, -3.0f, 300.0f),
		Vector3(0.0f),
		Vector3(1.0f, 2.5f, 1.0f)
	);

	for (int i = 0; i < mLevel; i++) {
		const static int RANDOM_POS_X = 1000;
		const static float POS_X_SUB = 0.1f;
		const static int RANDOM_SCALE = 3;
		const static float OFFSET_SCALE = 1.0f;
		transform.pos.x = ((rand() % RANDOM_POS_X) * POS_X_SUB) - ((RANDOM_POS_X * POS_X_SUB) / 2.0f);
		transform.scale.x += (rand() % RANDOM_SCALE) + OFFSET_SCALE;
		mGameObjectList->setGameObjectListToWorld(new Obstract(transform, mMoveSpeed));
	}
}

//-------------------------------------------------------------------------------------------------
/// �X�s�[�h�ύX
void ObstractManager::changeSpeed()
{
	for (const auto objs : mGameObjectList->findGameObjects(GameObjectTag::Ground)) {
		Ground* obj = (Ground*)objs;
		obj->setMoveSpeed(mMoveSpeed);
	}
	for (const auto objs : mGameObjectList->findGameObjects(GameObjectTag::Obstract)) {
		Obstract* obj = (Obstract*)objs;
		obj->setMoveSpeed(mMoveSpeed);
	}
}

} // namespace
// EOF