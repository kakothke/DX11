#include "Player.h"

//-------------------------------------------------------------------------------------------------
#include "MyOutputDebugString.h" 
#include "ResourceFileName.h"
#include "InputManager.h"
#include "Math.h"
#include "Sound.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// 定数
/// ターゲットからのデフォルト距離
const static float DEFINE_TARGET_DISTANCE = 100.0f;
/// 最大移動速度
const static float DEFINE_MAX_VELOCITY = 1.0f;
/// 加速度
const static float DEFINE_MOVE_SPEED = 10.0f;
/// 連続でショットを撃てる時間
const static float DEFINE_SHOT_TIME = 0.05f;
/// ショット時のアニメーション用
const static Vector2 DEFINE_SHOT_SIZE = Vector2(1.5f, 0.5f);

//-------------------------------------------------------------------------------------------------
/// シングルトンクラス
const static auto INPUT_MANAGER = InputManager::getInst();
const static auto FPS = Fps::getInst();
const static auto SOUND = Sound::getInst();

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Player::Player()
	: mRenderer()
	, mTargetPos()
	, mTargetDistance(DEFINE_TARGET_DISTANCE)
	, mMoveVelocity(0)
{
	// 描画設定
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::Player));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));
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
/// 移動速度を取得する
/// @return 移動速度
const Vector2& Player::moveVelocity()
{
	return mMoveVelocity;
}

//-------------------------------------------------------------------------------------------------
/// ターゲットの位置を設定する
/// @param aPos ターゲットの位置
void Player::setTargetPos(const Vector3& aPos)
{
	mTargetPos = aPos;
}

//-------------------------------------------------------------------------------------------------
/// 移動
void Player::move()
{
	// 入力
	Vector2 inputAxis = INPUT_MANAGER->getAxes();

	// 斜め入力
	float maxVelocity = DEFINE_MAX_VELOCITY;
	if (inputAxis.SqrMagnitude() == 2) {
		maxVelocity /= sqrtf(2);
	}

	// 移動
	if (inputAxis.x > 0) {
		mMoveVelocity.x = Math::Lerp(mMoveVelocity.x, maxVelocity, FPS->deltaTime() * DEFINE_MOVE_SPEED);
	}
	if (inputAxis.x < 0) {
		mMoveVelocity.x = Math::Lerp(mMoveVelocity.x, -maxVelocity, FPS->deltaTime() * DEFINE_MOVE_SPEED);
	}
	if (inputAxis.y > 0) {
		mMoveVelocity.y = Math::Lerp(mMoveVelocity.y, maxVelocity, FPS->deltaTime() * DEFINE_MOVE_SPEED);
	}
	if (inputAxis.y < 0) {
		mMoveVelocity.y = Math::Lerp(mMoveVelocity.y, -maxVelocity, FPS->deltaTime() * DEFINE_MOVE_SPEED);
	}
	// 静止
	if (inputAxis.x == 0) {
		mMoveVelocity.x = Math::Lerp(mMoveVelocity.x, 0, FPS->deltaTime() * DEFINE_MOVE_SPEED);
	}
	if (inputAxis.y == 0) {
		mMoveVelocity.y = Math::Lerp(mMoveVelocity.y, 0, FPS->deltaTime() * DEFINE_MOVE_SPEED);
	}

	// トランスフォーム更新
	Vector2 angle = mMoveVelocity * FPS->deltaTime();
	mTransform.rot *= Quaternion::AxisAngle(mTransform.Up(), -angle.x);
	mTransform.rot *= Quaternion::AxisAngle(mTransform.Right(), angle.y);
	mTransform.pos = mTargetPos + mTransform.rot * Vector3::back * mTargetDistance;
}

//-------------------------------------------------------------------------------------------------
/// ショット
void Player::shot()
{
	static float timer = 0;
	if (INPUT_MANAGER->getInput(InputCode::OK)) {
		// ショット
		if (timer == 0) {
			// SE再生
			SOUND->playOneShot((int)SoundList::SE_Shot);
			// 体を縮ませる
			mTransform.scale.x = DEFINE_SHOT_SIZE.x;
			mTransform.scale.y = DEFINE_SHOT_SIZE.y;
		}
		// タイマー更新
		if (timer < DEFINE_SHOT_TIME) {
			timer += FPS->deltaTime();
		} else {
			timer = 0;
		}
	} else if (timer > 0) {
		// ショットボタンを離したらタイマーリセット
		timer = 0;
	}
	// ショットを撃って体が縮んでいたら戻す
	if (mTransform.scale != Vector3(0)) {
		mTransform.scale.x -= 10.0f * FPS->deltaTime();
		mTransform.scale.y += 10.0f * FPS->deltaTime();
		mTransform.scale.x = Math::Clamp(mTransform.scale.x, 1.0f, DEFINE_SHOT_SIZE.x);
		mTransform.scale.y = Math::Clamp(mTransform.scale.y, DEFINE_SHOT_SIZE.y, 1.0f);
	}
}

} // namespace
// EOF
