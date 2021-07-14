#include "GameCamera.h"

//-------------------------------------------------------------------------------------------------
#include "InputManager.h"
#include "Math.h"
#include "Player.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto FPS = Fps::getInst();
const static auto INPUT_MANAGER = InputManager::getInst();

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
GameCamera::GameCamera()
	: mKatamuki(1.0f)
{
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
GameCamera::~GameCamera()
{
}

//-------------------------------------------------------------------------------------------------
/// 更新
void GameCamera::update()
{
	// 定数
	const static auto PLAYER_OBJ = (Player*)mGameObjectList->findWorldGameObject(GameObjectTag::Player);
	const static float NORMAL_KATAMUKI_LEVEL = 1.0f;
	const static float UP_KATAMUKI_LEVEL = NORMAL_KATAMUKI_LEVEL * 2.0f;
	const static float DOWN_KATAMUKI_LEVEL = NORMAL_KATAMUKI_LEVEL / 2.0f;
	const static Vector3 LOCAL_POS = Vector3(0.0f, 2.0f, -20.0f);

	if (PLAYER_OBJ->activeSelf()) {
		// プレイヤーの位置
		Vector3 playerPos = PLAYER_OBJ->transform().pos - PLAYER_OBJ->transform().localPos;

		// カメラ傾き度更新
		float speed = 10.0f * FPS->deltaTime();
		if (INPUT_MANAGER->axesRaw().y == 1) {
			// 上キーを押したら
			if (mKatamuki != UP_KATAMUKI_LEVEL) {
				mKatamuki = Math::Lerp(mKatamuki, UP_KATAMUKI_LEVEL, speed);
			}
		} if (INPUT_MANAGER->axesRaw().y == -1) {
			// 下キーを押したら
			if (mKatamuki != DOWN_KATAMUKI_LEVEL) {
				mKatamuki = Math::Lerp(mKatamuki, DOWN_KATAMUKI_LEVEL, speed);
			}
		} else {
			// 通常
			if (mKatamuki != NORMAL_KATAMUKI_LEVEL) {
				mKatamuki = Math::Lerp(mKatamuki, NORMAL_KATAMUKI_LEVEL, speed);
			}
		}
		float rotY = INPUT_MANAGER->axes().x * -mKatamuki;
		float rotZ = rotY * 6.0f;

		// プレイヤーを親オブジェクトとして連動させる
		mTransform.pos = playerPos;

		// ローカル位置を変更
		float localPosX = rotY * 2.0f;
		mTransform.localPos = LOCAL_POS;
		mTransform.localPos.x = localPosX;
		mTransform.localRot = Quaternion::Euler(Vector3(0.0f, rotY, rotZ));
	}
}

//-------------------------------------------------------------------------------------------------
/// 描画
void GameCamera::draw()
{
}

} // namespace
// EOF
