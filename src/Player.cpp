#include "Player.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "InputManager.h"
#include "Math.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto INPUT_MANAGER = InputManager::getInst();
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Player::Player()
	: mMoveSpeed(20.0f)
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
	if (INPUT_MANAGER->axesRaw().y == 1) {
		// 高速移動
		if (mMoveSpeed != UP_SPEED_LEVEL) {
			mMoveSpeed = Math::Lerp(mMoveSpeed, UP_SPEED_LEVEL, speed);
		}
	} else if (INPUT_MANAGER->axesRaw().y == -1) {
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

} // namespace
// EOF
