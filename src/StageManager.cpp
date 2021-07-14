#include "StageManager.h"

//-------------------------------------------------------------------------------------------------
#include "Ground.h"
#include "Obstract.h"
#include "MoveLineEffect.h"
#include "Math.h"
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
	, mInstanceMoveLineEffectTimer(0.0f)
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
	const static auto PLAYER_OBJ = mGameObjectList->findWorldGameObject(GameObjectTag::Player);
	if (PLAYER_OBJ->activeSelf()) {
		updateLevel();
		instanceObj();
	} else {
		missEvent();
	}
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
	const static float LEVEL_UP_TIME = 5.0f;
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

	MyOutputDebugString(TEXT("level:%d / cnt:%d\n"), mLevel, mInstanceObstractCount);
}

//-------------------------------------------------------------------------------------------------
/// �I�u�W�F�N�g�𐶐�����
void StageManager::instanceObj()
{
	const static float INSTANCE_OBSTRACT_TIME = 0.2f;
	const static float INSTANCE_GROUND_TIME = 0.1f;
	const static float INSTANCE_MOVE_LINE_EFFECT_TIME = 0.1f;
	const static int INSTANCE_GROUND_CNT = 2;

	// ��Q������
	if (mInstanceObstractTimer > INSTANCE_OBSTRACT_TIME) {
		mInstanceObstractTimer = 0.0f;
		for (int i = 0; i < mInstanceObstractCount; i++) {
			Obstract* obj = new Obstract();
			mGameObjectList->instanceToWorldAlpha(obj);
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
			mGameObjectList->instanceToWorldAlpha(obj);
			obj->setMoveSpeed(mMoveSpeed);
		}
	} else {
		mInstanceGroundTimer += FPS->deltaTime();
	}

	// �ړ�������
	if (mInstanceMoveLineEffectTimer > INSTANCE_MOVE_LINE_EFFECT_TIME) {
		mInstanceMoveLineEffectTimer = 0.0f;
		for (int i = 0; i < mInstanceObstractCount; i++) {
			MoveLineEffect* obj = new MoveLineEffect();
			mGameObjectList->instanceToWorldAlpha(obj);
			obj->setMoveSpeed(mMoveSpeed);
		}
	} else {
		mInstanceMoveLineEffectTimer += FPS->deltaTime();
	}
}

//-------------------------------------------------------------------------------------------------
/// �X�s�[�h�ύX
void StageManager::changeSpeed()
{
	for (const auto objs : mGameObjectList->findWorldGameObjectsAlpha(GameObjectTag::Ground)) {
		Ground* obj = (Ground*)objs;
		obj->setMoveSpeed(mMoveSpeed);
	}
	for (const auto objs : mGameObjectList->findWorldGameObjectsAlpha(GameObjectTag::Obstract)) {
		Obstract* obj = (Obstract*)objs;
		obj->setMoveSpeed(mMoveSpeed);
	}
	for (const auto objs : mGameObjectList->findWorldGameObjectsAlpha(GameObjectTag::Effect_MoveLine)) {
		MoveLineEffect* obj = (MoveLineEffect*)objs;
		obj->setMoveSpeed(mMoveSpeed);
	}
}

//-------------------------------------------------------------------------------------------------
/// �~�X�C�x���g
void StageManager::missEvent()
{
	const static float MISS_SPEED_DOWN = 2.0f;
	if (mMoveSpeed != 0) {
		mMoveSpeed = Math::Lerp(mMoveSpeed, 0.0f, MISS_SPEED_DOWN * FPS->deltaTime());
		changeSpeed();
	}
}

} // namespace
// EOF