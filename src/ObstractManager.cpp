#include "ObstractManager.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// 定数
const static float DEFINE_INSTANCE_TIME = 0.2f;
const static float DEFINE_LEVEL_UP_TIME = 5.0f;
const static float DEFINE_MOVE_SPEED = 100.0f;
const static float DEFINE_MOVE_UP = 5.0f;

//-------------------------------------------------------------------------------------------------
/// シングルトン
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
ObstractManager::ObstractManager()
	: mSpeed(DEFINE_MOVE_SPEED)
	, mLevel(1)
{
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
ObstractManager::~ObstractManager()
{
}

//-------------------------------------------------------------------------------------------------
/// 更新
void ObstractManager::update()
{
	// レベルアップ
	static float time = 0.0f;
	if (time > DEFINE_LEVEL_UP_TIME * mLevel) {
		time = 0.0f;
		mLevel++;
		mSpeed += DEFINE_MOVE_UP;
	} else {
		time += FPS->deltaTime();
	}

	// 生成
	instanceObj();

	// 地形更新
	for (auto itr = mGround.begin(); itr != mGround.end();) {
		if ((*itr)->activeSelf()) {
			// 更新
			(*itr)->update();
			itr++;
		} else {
			// 消去
			itr = mGround.erase(itr);
		}
	}
	// 障害物更新
	for (auto itr = mObstract.begin(); itr != mObstract.end();) {
		if ((*itr)->activeSelf()) {
			// 更新
			(*itr)->update();
			itr++;
		} else {
			// 消去
			itr = mObstract.erase(itr);
		}
	}
}

//-------------------------------------------------------------------------------------------------
/// 描画
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
/// 当たり判定
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
/// オブジェクトを生成する
void ObstractManager::instanceObj()
{
	static float groundTimer = 0.0f;
	static float obstractTimer = 0.0f;
	// 地上生成
	if (groundTimer > DEFINE_INSTANCE_TIME / 2.0f) {
		groundTimer = 0.0f;
		instanceGround();
	} else {
		groundTimer += FPS->deltaTime();
	}
	// 障害物生成
	if (obstractTimer > DEFINE_INSTANCE_TIME) {
		obstractTimer = 0.0f;
		instanceObstract();
	} else {
		obstractTimer += FPS->deltaTime();
	}
}

//-------------------------------------------------------------------------------------------------
/// 地上を生成する
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
/// 障害物を生成する
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
/// スピード変更
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