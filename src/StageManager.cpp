#include "StageManager.h"

//-------------------------------------------------------------------------------------------------
#include "Ground.h"
#include "Obstract.h"
#include "MyOutputDebugString.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
StageManager::StageManager()
	: mLevelUpTimer(0.0f)
	, mInstanceObstractTimer(0.0f)
	, mInstanceGroundTimer(0.0f)
	, mMoveSpeed(100.0f)
	, mLevel(1)
	, mInstanceObstractCount(1)
{
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
StageManager::~StageManager()
{
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void StageManager::update()
{
	updateLevel();
	instanceObj();
}

//-------------------------------------------------------------------------------------------------
/// �`��
void StageManager::draw()
{
}

//-------------------------------------------------------------------------------------------------
/// ���x���X�V
void StageManager::updateLevel()
{
	// �萔
	const static float LEVEL_UP_TIME = 10.0f;
	const static float SPEED_UP = 5.0f;
	const static int INSTANCE_OBSTRACT_COUNT_UP = 5;

	// ���x���A�b�v
	if (mLevelUpTimer > LEVEL_UP_TIME) {
		mLevelUpTimer = 0.0f;
		mLevel++;
		mMoveSpeed += SPEED_UP;
		changeSpeed();
		// ��Q���������A�b�v
		if (mLevel % INSTANCE_OBSTRACT_COUNT_UP == 0) {
			mInstanceObstractCount++;
		}
	} else {
		mLevelUpTimer += FPS->deltaTime();
	}
}

//-------------------------------------------------------------------------------------------------
/// �I�u�W�F�N�g�𐶐�����
void StageManager::instanceObj()
{
	const static float INSTANCE_OBSTRACT_TIME = 0.2f;
	const static float INSTANCE_GROUND_TIME = 0.1f;
	const static int INSTANCE_GROUND_CNT = 2;

	// ��Q������
	if (mInstanceObstractTimer > INSTANCE_OBSTRACT_TIME) {
		mInstanceObstractTimer = 0.0f;
		for (int i = 0; i < mInstanceObstractCount; i++) {
			Obstract* obj = new Obstract();
			mGameObjectList->setGameObjectListToWorld(obj, 0, true);
			obj->setMoveSpeed(mMoveSpeed);
		}
	} else {
		mInstanceObstractTimer += FPS->deltaTime();
	}

	// �n�㐶��
	if (mInstanceGroundTimer > INSTANCE_GROUND_TIME) {
		mInstanceGroundTimer = 0.0f;
		for (int i = 0; i < INSTANCE_GROUND_CNT; i++) {
			Ground* obj = new Ground();
			mGameObjectList->setGameObjectListToWorld(obj, 0, true);
			obj->setMoveSpeed(mMoveSpeed);
		}
	} else {
		mInstanceGroundTimer += FPS->deltaTime();
	}
}

//-------------------------------------------------------------------------------------------------
/// �X�s�[�h�ύX
void StageManager::changeSpeed()
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