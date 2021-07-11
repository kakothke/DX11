#include "Player.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "InputManager.h"
#include "Math.h"
#include "PlayerBooster.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto INPUT_MANAGER = InputManager::getInst();
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Player::Player()
	: mMoveSpeed(20.0f)
	, mInstanceBoosterTimer(0.0f)
{
	// タグ設定
	setTag(GameObjectTag::Player);

	// 描画設定
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::Player));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
Player::~Player()
{
}

//-------------------------------------------------------------------------------------------------
/// 更新
void Player::update()
{
	move();
	shot();
	instanceEffect();
}

//-------------------------------------------------------------------------------------------------
/// 描画
void Player::draw()
{
	mRenderer.render(mTransform);
}

//-------------------------------------------------------------------------------------------------
/// 移動
void Player::move()
{
	// 定数
	const static float NORMAL_SPEED_LEVEL = 20.0f;
	const static float UP_SPEED_LEVEL = NORMAL_SPEED_LEVEL * 2.0f;
	const static float DOWN_SPEED_LEVEL = NORMAL_SPEED_LEVEL / 2.0f;

	float speed = 10.0f * FPS->deltaTime();
	float axisY = INPUT_MANAGER->axesRaw().y;
	if (axisY == 1) {
		// 高速移動
		if (mMoveSpeed != UP_SPEED_LEVEL) {
			mMoveSpeed = Math::Lerp(mMoveSpeed, UP_SPEED_LEVEL, speed);
		}
	} else if (axisY == -1) {
		// 減速移動
		if (mMoveSpeed != DOWN_SPEED_LEVEL) {
			mMoveSpeed = Math::Lerp(mMoveSpeed, DOWN_SPEED_LEVEL, speed);
		}
	} else {
		// 通常移動
		if (mMoveSpeed != NORMAL_SPEED_LEVEL) {
			mMoveSpeed = Math::Lerp(mMoveSpeed, NORMAL_SPEED_LEVEL, speed);
		}
	}

	// 移動
	float move = INPUT_MANAGER->axesRaw().x * mMoveSpeed;
	float rot = INPUT_MANAGER->axes().x * -mMoveSpeed * 2.0f;
	mTransform.pos.x += move * FPS->deltaTime();
	mTransform.rot = Quaternion::Euler(Vector3(0.0f, 0.0f, rot));
}

//-------------------------------------------------------------------------------------------------
/// ショット
void Player::shot()
{
}

//-------------------------------------------------------------------------------------------------
/// エフェクト生成
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
		} else if (axisY == -1) {
			transform.scale -= SCALE_RANGE;
		}
		mGameObjectList->setGameObjectListToWorld(new PlayerBooster(transform), 0, true);
	} else {
		mInstanceBoosterTimer += FPS->deltaTime();
	}
}

} // namespace
// EOF
