#include "TestPlayer.h"

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
/// 移動速度
const static float DEFINE_MOVE_SPEED = 50.0f;
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
TestPlayer::TestPlayer()
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
/// デストラクタ
TestPlayer::~TestPlayer()
{
}

//-------------------------------------------------------------------------------------------------
/// 更新
void TestPlayer::update()
{
	move();
	shot();

	for (auto itr = mPlayerBullet.begin(); itr != mPlayerBullet.end();) {
		if ((*itr)->activeSelf()) {
			(*itr)->update();
			itr++;
		} else {
			itr = mPlayerBullet.erase(itr);
		}
	}
}

//-------------------------------------------------------------------------------------------------
/// 描画
void TestPlayer::draw()
{
	mRenderer.render(mTransform);

	for (const auto bullet : mPlayerBullet) {
		bullet->draw();
	}
}

//-------------------------------------------------------------------------------------------------
/// 移動速度を取得する
/// @return 移動速度
const Vector2& TestPlayer::moveVelocity()
{
	return mMoveVelocity;
}

//-------------------------------------------------------------------------------------------------
/// ターゲットの位置を設定する
/// @param aPos ターゲットの位置
void TestPlayer::setTargetPos(const Vector3& aPos)
{
	mTargetPos = aPos;
}

//-------------------------------------------------------------------------------------------------
/// 移動
void TestPlayer::move()
{
	// 移動
	mMoveVelocity = INPUT_MANAGER->axes();
	if (mMoveVelocity.Magnitude() > 1.0f) {
		mMoveVelocity = mMoveVelocity.Normalized();
	}

	// トランスフォーム更新
	Vector2 angle = mMoveVelocity * FPS->deltaTime() * DEFINE_MOVE_SPEED;
	mTransform.rot *= Quaternion::AxisAngle(-mTransform.Up(), angle.x);
	mTransform.rot *= Quaternion::AxisAngle(mTransform.Right(), angle.y);
	mTransform.pos = mTargetPos + mTransform.rot * Vector3::back * mTargetDistance;
}

//-------------------------------------------------------------------------------------------------
/// ショット
void TestPlayer::shot()
{
	static float timer = 0.0f;
	if (INPUT_MANAGER->getButton(InputCode::OK)) {
		// ショット
		if (timer == 0.0f) {
			// SE再生
			SOUND->playOneShot((int)SoundList::SE_Shot);
			// 体を縮ませる
			mTransform.scale.x = DEFINE_SHOT_SIZE.x;
			mTransform.scale.y = DEFINE_SHOT_SIZE.y;
			// 弾生成
			Transform bulletTransform;
			bulletTransform = mTransform;
			mPlayerBullet.emplace_back(std::make_shared<PlayerBullet>(bulletTransform, mTargetPos));
		}
		// タイマー更新
		if (timer < DEFINE_SHOT_TIME) {
			timer += FPS->deltaTime();
		} else {
			timer = 0.0f;
		}
	} else if (timer > 0.0f) {
		// ショットボタンを離したらタイマーリセット
		timer = 0.0f;
	}
	// ショットを撃って体が縮んでいたら戻す
	if (mTransform.scale != Vector3(0.0f)) {
		mTransform.scale.x -= 10.0f * FPS->deltaTime();
		mTransform.scale.y += 10.0f * FPS->deltaTime();
		mTransform.scale.x = Math::Clamp(mTransform.scale.x, 1.0f, DEFINE_SHOT_SIZE.x);
		mTransform.scale.y = Math::Clamp(mTransform.scale.y, DEFINE_SHOT_SIZE.y, 1.0f);
	}
}

} // namespace
// EOF
