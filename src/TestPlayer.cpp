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
const static auto INPUT_MANAGER = InputManager::getInst();
const static auto FPS = Fps::getInst();
const static auto SOUND = Sound::getInst();

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
TestPlayer::TestPlayer()
	: mRenderer()
	, mTargetDistance(100.0f)
	, mMoveVelocity(0)
{
	// タグ
	setTag(GameObjectTag::Player);

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
	// ターゲット位置更新
	const static auto BOSS_OBJ = mGameObjectList->findGameObject(GameObjectTag::Boss);
	mTargetPos = BOSS_OBJ->transform().pos;

	// 移動
	move();
	// ショット
	shot();
}

//-------------------------------------------------------------------------------------------------
/// 描画
void TestPlayer::draw()
{
	mRenderer.render(mTransform);
}

//-------------------------------------------------------------------------------------------------
/// 移動速度を取得する
/// @return 移動速度
const Vector2& TestPlayer::moveVelocity()
{
	return mMoveVelocity;
}

//-------------------------------------------------------------------------------------------------
/// 移動
void TestPlayer::move()
{
	const static float MOVE_SPEED = 50.0f;

	// 移動
	mMoveVelocity = INPUT_MANAGER->axes();
	if (mMoveVelocity.Magnitude() > 1.0f) {
		mMoveVelocity = mMoveVelocity.Normalized();
	}

	// トランスフォーム更新
	Vector2 angle = mMoveVelocity * FPS->deltaTime() * MOVE_SPEED;
	mTransform.rot *= Quaternion::AxisAngle(-mTransform.Up(), angle.x);
	mTransform.rot *= Quaternion::AxisAngle(mTransform.Right(), angle.y);
	mTransform.pos = mTargetPos + mTransform.rot * Vector3::back * mTargetDistance;
}

//-------------------------------------------------------------------------------------------------
/// ショット
void TestPlayer::shot()
{
	const static float RAPID_SHOT_TIME = 0.05f;
	const static float RESET_SCALE_TIME = 10.0f;
	const static Vector2 SHOT_SCALE = Vector2(1.5f, 0.5f);

	if (INPUT_MANAGER->getButton(InputCode::OK)) {
		// ショット
		if (mRapidShotTimer == 0.0f) {
			// SE再生
			SOUND->playOneShot((int)SoundList::SE_Shot);
			// 体を縮ませる
			mTransform.scale = SHOT_SCALE;
			// 弾生成
			Transform bulletTransform;
			bulletTransform = mTransform;
			mGameObjectList->instanceToWorldAlpha(new PlayerBullet(bulletTransform, mTargetPos));
		}
		// タイマー更新
		if (mRapidShotTimer < RAPID_SHOT_TIME) {
			mRapidShotTimer += FPS->deltaTime();
		} else {
			mRapidShotTimer = 0.0f;
		}
	} else {
		mRapidShotTimer = 0.0f;
	}
	// ショットを撃って体が縮んでいたら戻す
	if (mTransform.scale != Vector3(0.0f)) {
		mTransform.scale.x -= RESET_SCALE_TIME * FPS->deltaTime();
		mTransform.scale.y += RESET_SCALE_TIME * FPS->deltaTime();
		mTransform.scale.x = Math::Clamp(mTransform.scale.x, 1.0f, SHOT_SCALE.x);
		mTransform.scale.y = Math::Clamp(mTransform.scale.y, SHOT_SCALE.y, 1.0f);
	}
}

} // namespace
// EOF
