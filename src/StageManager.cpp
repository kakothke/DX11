#include "StageManager.h"

//-------------------------------------------------------------------------------------------------
#include "Ground.h"
#include "Obstract.h"
#include "MoveLineEffect.h"
#include "Math.h"
#include "Random.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
StageManager::StageManager()
	: mLevelUpTimer(0.0f)
	, mInstanceObstractTimer(0.0f)
	, mInstanceGroundTimer(0.0f)
	, mInstanceMoveLineEffectTimer(0.0f)
	, mScore(0.0f)
	, mMoveSpeed(100.0f)
	, mLevel(1)
	, mInstanceObstractCount(1)
	, mMissFlag(false)
{
	Random::RandomSeed();
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
StageManager::~StageManager()
{
}

//-------------------------------------------------------------------------------------------------
/// 更新
void StageManager::update()
{
	if (!mMissFlag) {
		updateLevel();
		instanceObj();
	} else {
		missEvent();
	}
}

//-------------------------------------------------------------------------------------------------
/// 描画
void StageManager::draw()
{
}

//-------------------------------------------------------------------------------------------------
/// メートルを返す
int StageManager::getScore()
{
	return (int)mScore;
}

//-------------------------------------------------------------------------------------------------
/// ミスフラグを立てる
void StageManager::setMissFlagTrue()
{
	mMissFlag = true;
}

//-------------------------------------------------------------------------------------------------
/// レベル更新
void StageManager::updateLevel()
{
	// 定数
	const static float LEVEL_UP_TIME = 5.0f;
	const static float SPEED_UP = 5.0f;
	const static float METER_SPEED = 2.0f;
	const static int INSTANCE_OBSTRACT_COUNT_UP = 5;

	// レベルアップ
	if (mLevelUpTimer > LEVEL_UP_TIME) {
		mLevelUpTimer = 0.0f;
		mLevel++;
		mMoveSpeed += SPEED_UP;
		changeSpeed();
		// 障害物生成数アップ
		if (mLevel % INSTANCE_OBSTRACT_COUNT_UP == 0) {
			mInstanceObstractCount++;
		}
	} else {
		mLevelUpTimer += mFps->deltaTime();
	}

	// スコア
	mScore += (mMoveSpeed / METER_SPEED) * mFps->deltaTime();
}

//-------------------------------------------------------------------------------------------------
/// オブジェクトを生成する
void StageManager::instanceObj()
{
	const static float INSTANCE_OBSTRACT_TIME = 0.2f;
	const static float INSTANCE_GROUND_TIME = 0.1f;
	const static float INSTANCE_MOVE_LINE_EFFECT_TIME = 0.1f;
	const static int INSTANCE_GROUND_CNT = 2;

	// 障害物生成
	if (mInstanceObstractTimer > INSTANCE_OBSTRACT_TIME) {
		mInstanceObstractTimer = 0.0f;
		for (int i = 0; i < mInstanceObstractCount; i++) {
			Obstract* obj = new Obstract();
			mGameObjectList->instanceToWorldAlpha(obj);
			obj->setMoveSpeed(mMoveSpeed);
		}
	} else {
		mInstanceObstractTimer += mFps->deltaTime();
	}

	// 地上生成
	if (mInstanceGroundTimer > INSTANCE_GROUND_TIME) {
		mInstanceGroundTimer = 0.0f;
		for (int i = 0; i < INSTANCE_GROUND_CNT; i++) {
			Ground* obj = new Ground();
			mGameObjectList->instanceToWorldAlpha(obj);
			obj->setMoveSpeed(mMoveSpeed);
		}
	} else {
		mInstanceGroundTimer += mFps->deltaTime();
	}

	// 移動線生成
	if (mInstanceMoveLineEffectTimer > INSTANCE_MOVE_LINE_EFFECT_TIME) {
		mInstanceMoveLineEffectTimer = 0.0f;
		for (int i = 0; i < mInstanceObstractCount; i++) {
			MoveLineEffect* obj = new MoveLineEffect();
			mGameObjectList->instanceToWorldAlpha(obj);
			obj->setMoveSpeed(mMoveSpeed);
		}
	} else {
		mInstanceMoveLineEffectTimer += mFps->deltaTime();
	}
}

//-------------------------------------------------------------------------------------------------
/// スピード変更
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
/// ミスイベント
void StageManager::missEvent()
{
	const static float MISS_SPEED_DOWN = 2.0f;
	if (mMoveSpeed != 0) {
		mMoveSpeed = Math::Lerp(mMoveSpeed, 0.0f, MISS_SPEED_DOWN * mFps->deltaTime());
		changeSpeed();
	}
}

} // namespace
// EOF